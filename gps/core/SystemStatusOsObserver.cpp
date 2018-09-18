/* Copyright (c) 2015-2017, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation, nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#define LOG_TAG "LocSvc_SystemStatusOsObserver"

#include <string>
#include <cinttypes>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <iterator>
#include <algorithm>

#include <MsgTask.h>
#include <SystemStatusOsObserver.h>

#include <DataItemId.h>
#include <IDataItemCore.h>

#include <IClientIndex.h>
#include <IDataItemIndex.h>
#include <IndexFactory.h>



#include <DataItemsFactoryProxy.h>

#include <platform_lib_log_util.h>

namespace loc_core
{

#define BREAK_IF_ZERO(ERR,X) if(0==(X)) {result = (ERR); break;}
#define BREAK_IF_NON_ZERO(ERR,X) if(0!=(X)) {result = (ERR); break;}

SystemStatusOsObserver::SystemStatusOsObserver(const MsgTask* msgTask) :
    mAddress ("SystemStatusOsObserver"),
    mClientIndex(IndexFactory <IDataItemObserver *, DataItemId> :: createClientIndex ()),
    mDataItemIndex(IndexFactory <IDataItemObserver *, DataItemId> :: createDataItemIndex ())
{
    int result = -1;
    ENTRY_LOG ();
    do {
        BREAK_IF_ZERO (1, mClientIndex);
        BREAK_IF_ZERO (2, mDataItemIndex);
        mContext.mMsgTask = msgTask;
        result = 0;
    } while (0);
    EXIT_LOG_WITH_ERROR ("%d",result);
}

SystemStatusOsObserver :: ~SystemStatusOsObserver ()
{

template <typename CINT, typename COUT>
COUT SystemStatusOsObserver::containerTransfer(CINT& inContainer) {
    COUT outContainer(0);
    for (auto item : inContainer) {
        outContainer.insert(outContainer.begin(), item);
    }
    return outContainer;
}

SystemStatusOsObserver::~SystemStatusOsObserver() {

    // Close data-item library handle
    DataItemsFactoryProxy::closeDataItemLibraryHandle();

    // Destroy cache
    map <DataItemId, IDataItemCore *> :: iterator citer = mDataItemCache.begin ();
    for (; citer != mDataItemCache.end (); ++citer) {
        if (citer->second != NULL) { delete citer->second; }
    }

    mDataItemCache.clear ();
    delete mClientIndex;
    delete mDataItemIndex;
    mClientIndex = NULL;
    mDataItemIndex = NULL;


    mDataItemCache.clear();
}

void SystemStatusOsObserver::setSubscriptionObj(IDataItemSubscription* subscriptionObj)
{
    struct SetSubsObj : public LocMsg {
        ObserverContext& mContext;
        IDataItemSubscription* mSubsObj;
        inline SetSubsObj(ObserverContext& context, IDataItemSubscription* subscriptionObj) :
                mContext(context), mSubsObj(subscriptionObj) {}
        void proc() const {
            mContext.mSubscriptionObj = mSubsObj;

            if (!mContext.mSSObserver->mDataItemToClients.empty()) {
                list<DataItemId> dis(
                        containerTransfer<unordered_set<DataItemId>, list<DataItemId>>(
                                mContext.mSSObserver->mDataItemToClients.getKeys()));
                mContext.mSubscriptionObj->subscribe(dis, mContext.mSSObserver);
                mContext.mSubscriptionObj->requestData(dis, mContext.mSSObserver);
            }
        }
    };

    if (nullptr == subscriptionObj) {
        LOC_LOGw("subscriptionObj is NULL");
    } else {
        mContext.mMsgTask->sendMsg(new SetSubsObj(mContext, subscriptionObj));
    }

}

/******************************************************************************
 Message proc
******************************************************************************/

void SystemStatusOsObserver :: HandleSubscribeReq :: proc () const {

    int result = 0;
    ENTRY_LOG ();
    do {
        if (mDataItemList.empty ()) {
            LOC_LOGV("mDataItemList is empty. Nothing to do. Exiting");
            result = 0;
            break;
        }
        //mDataItemList.sort ();
        // Handle First Response
        list <DataItemId> pendingFirstResponseList;
        this->mParent->mClientIndex->add (this->mClient, mDataItemList, pendingFirstResponseList);

        // Do not send first response for only pendingFirstResponseList,
        // instead send for all the data items  (present in the cache) that
        // have been subscribed for each time.
        this->mParent->sendFirstResponse (mDataItemList, this->mClient);

        list <DataItemId> yetToSubscribeDataItemsList;
        this->mParent->mDataItemIndex->add (this->mClient, mDataItemList, yetToSubscribeDataItemsList);
        // Send subscription list to framework
        if (!yetToSubscribeDataItemsList.empty ()) {
            this->mParent->mContext.mSubscriptionObj->subscribe
            (
                yetToSubscribeDataItemsList,
                this->mParent
            );
            LOC_LOGD ("Subscribe Request sent to framework for the following data items");
            this->mParent->logMe (yetToSubscribeDataItemsList);
        }

    } while (0);
    EXIT_LOG_WITH_ERROR ("%d", result);
    return;
}

void SystemStatusOsObserver :: HandleUpdateSubscriptionReq :: proc () const {
    int result = 0;
    ENTRY_LOG ();
    do {
        if (mDataItemList.empty ()) {
            LOC_LOGV("mDataItemList is empty. Nothing to do. Exiting");
            result = 0;
            break;
        }
        //mDataItemList.sort ();
        list <DataItemId> currentlySubscribedList;
        this->mParent->mClientIndex->getSubscribedList (this->mClient, currentlySubscribedList);
        list <DataItemId> removeDataItemList;
        set_difference (currentlySubscribedList.begin (), currentlySubscribedList.end (),
                       mDataItemList.begin (), mDataItemList.end (),
                       inserter (removeDataItemList,removeDataItemList.begin ()));
        // Handle First Response
        list <DataItemId> pendingFirstResponseList;
        this->mParent->mClientIndex->add (this->mClient, mDataItemList, pendingFirstResponseList);
        // Send First Response
        this->mParent->sendFirstResponse (pendingFirstResponseList, this->mClient);

        list <DataItemId> yetToSubscribeDataItemsList;
        this->mParent->mDataItemIndex->add (this->mClient, mDataItemList, yetToSubscribeDataItemsList);
        // Send subscription list to framework
        if (!yetToSubscribeDataItemsList.empty ()) {
            this->mParent->mContext.mSubscriptionObj->subscribe
            (
                yetToSubscribeDataItemsList,
                this->mParent
            );
            LOC_LOGD ("Subscribe Request sent to framework for the following data items");
            this->mParent->logMe (yetToSubscribeDataItemsList);
        }

        list <DataItemId> unsubscribeList;
        list <DataItemId> unused;
        this->mParent->mClientIndex->remove (this->mClient, removeDataItemList, unused);

        if (!this->mParent->mClientIndex->isSubscribedClient (this->mClient)) {
            this->mParent->mDataItemIndex->remove (list <IDataItemObserver *> (1,this->mClient), unsubscribeList);
        }
        if (!unsubscribeList.empty ()) {
            // Send unsubscribe to framework
            this->mParent->mContext.mSubscriptionObj->unsubscribe
            (
                unsubscribeList,
                this->mParent
            );
            LOC_LOGD ("Unsubscribe Request sent to framework for the following data items");
            this->mParent->logMe (unsubscribeList);
        }
    } while (0);
    EXIT_LOG_WITH_ERROR ("%d",result);
}

void SystemStatusOsObserver :: HandleRequestData :: proc () const {
    int result = 0;
    ENTRY_LOG ();

    do {
        if (mDataItemList.empty ()) {
            LOC_LOGV("mDataItemList is empty. Nothing to do. Exiting");
            result = 0;
            break;
        }
        //mDataItemList.sort ();
        list <DataItemId> yetToSubscribeDataItemsList;
        this->mParent->mClientIndex->add (this->mClient, mDataItemList, yetToSubscribeDataItemsList);
        this->mParent->mDataItemIndex->add (this->mClient, mDataItemList, yetToSubscribeDataItemsList);
        // Send subscription list to framework
        if (!mDataItemList.empty ()) {
            this->mParent->mContext.mSubscriptionObj->requestData
            (
                mDataItemList,
                this->mParent
            );
            LOC_LOGD ("Subscribe Request sent to framework for the following data items");
            this->mParent->logMe (yetToSubscribeDataItemsList);
        }

    } while (0);
    EXIT_LOG_WITH_ERROR ("%d",result);
}

void SystemStatusOsObserver :: HandleUnsubscribeReq :: proc () const {
    int result = 0;
    ENTRY_LOG ();
    do {
        if (mDataItemList.empty ()) {
            LOC_LOGV("mDataItemList is empty. Nothing to do. Exiting");
            result = 0;
            break;
        }
        //mDataItemList.sort ();
        list <DataItemId> unsubscribeList;
        list <DataItemId> unused;
        this->mParent->mClientIndex->remove (this->mClient, mDataItemList, unused);

        list <DataItemId> :: const_iterator it = mDataItemList.begin ();
        for (; it != mDataItemList.end (); ++it) {
            list <IDataItemObserver *> clientListSubs;
            list <IDataItemObserver *> clientListOut;
            this->mParent->mDataItemIndex->remove ((*it),
                                list <IDataItemObserver *> (1,this->mClient), clientListOut);
            // check if there are any other subscribed client for this data item id
            this->mParent->mDataItemIndex->getListOfSubscribedClients ( (*it), clientListSubs);
            if (clientListSubs.empty())
            {
                LOC_LOGD ("Client list subscribed is empty for dataitem - %d",(*it));
                unsubscribeList.push_back((*it));
            }
        }
        if (!unsubscribeList.empty ()) {
            // Send unsubscribe to framework
            this->mParent->mContext.mSubscriptionObj->unsubscribe
            (
                unsubscribeList,
                this->mParent
            );
            LOC_LOGD ("Unsubscribe Request sent to framework for the following data items");
            this->mParent->logMe (unsubscribeList);
        }
    } while (0);
    EXIT_LOG_WITH_ERROR ("%d",result);
}

void SystemStatusOsObserver :: HandleUnsubscribeAllReq :: proc () const {
    int result = 0;
    ENTRY_LOG ();
    do {
        list <IDataItemObserver *> clients (1, this->mClient);
        list <DataItemId> unsubscribeList;
        BREAK_IF_NON_ZERO (2, this->mParent->mClientIndex->remove (this->mClient));


        this->mParent->mDataItemIndex->remove (clients, unsubscribeList);
        if (!unsubscribeList.empty ()) {
            // Send unsubscribe to framework
            this->mParent->mContext.mSubscriptionObj->unsubscribe
            (
                unsubscribeList,
                this->mParent
            );
            LOC_LOGD ("Unsubscribe Request sent to framework for the following data items");
            this->mParent->logMe (unsubscribeList);
        }
    } while (0);
    EXIT_LOG_WITH_ERROR ("%d",result);
}

void SystemStatusOsObserver :: HandleNotify :: getListOfClients
 (const list <DataItemId> & dlist, list <IDataItemObserver *> & clients ) const {

     list <DataItemId> :: const_iterator it = dlist.begin ();
     for (; it != dlist.end (); ++it) {
         list <IDataItemObserver *> clientList;
         this->mParent->mDataItemIndex->getListOfSubscribedClients ( (*it), clientList);
         list <IDataItemObserver *> :: iterator citer = clientList.begin ();
         for (; citer != clientList.end (); ++citer) {
             clients.push_back (*citer);
         }
         clientList.clear ();
     }
     // remove duplicates
     clients.unique ();
}

void SystemStatusOsObserver :: HandleNotify :: proc () const {
    int result = 0;
    ENTRY_LOG ();
    do {
        // Update Cache with received data items and prepare
        // list of data items to be sent.
        list <IDataItemCore *> :: const_iterator it = mDList.begin ();
        list <DataItemId> dataItemIdsToBeSent;
        for (; it != mDList.end (); ++it) {
            bool dataItemUpdated = false;
            this->mParent->updateCache (*it, dataItemUpdated);
            if (dataItemUpdated) {
                dataItemIdsToBeSent.push_back ( (*it)->getId ());
            }
        }

        list <IDataItemObserver *> clientList;
        this->getListOfClients (dataItemIdsToBeSent, clientList);
        list <IDataItemObserver *> :: iterator citer = clientList.begin ();
        // Send data item to all subscribed clients
        LOC_LOGD ("LocTech-Label :: SystemStatusOsObserver :: Data Items Out");
        for (; citer != clientList.end (); ++citer) {
            do {
                list <DataItemId> dataItemIdsSubscribedByThisClient;
                list <DataItemId> dataItemIdsToBeSentForThisClient;
                this->mParent->mClientIndex->getSubscribedList (*citer, dataItemIdsSubscribedByThisClient);
                dataItemIdsSubscribedByThisClient.sort ();
                dataItemIdsToBeSent.sort ();
                set_intersection (dataItemIdsToBeSent.begin (),
                                 dataItemIdsToBeSent.end (),
                                 dataItemIdsSubscribedByThisClient.begin (),
                                 dataItemIdsSubscribedByThisClient.end (),
                                 inserter (dataItemIdsToBeSentForThisClient,
                                         dataItemIdsToBeSentForThisClient.begin ()));
                BREAK_IF_NON_ZERO (4,this->mParent->sendCachedDataItems (dataItemIdsToBeSentForThisClient, *citer));
                dataItemIdsSubscribedByThisClient.clear ();
                dataItemIdsToBeSentForThisClient.clear ();
            } while (0);
        }
    } while (0);
    EXIT_LOG_WITH_ERROR ("%d", result);
}

void SystemStatusOsObserver :: HandleTurnOn :: proc () const {
    int result = 0;
    ENTRY_LOG ();
    do {
        // Send action turn on to framework
        this->mParent->mContext.mFrameworkActionReqObj->turnOn(mDataItemId, mTimeOut);
    } while (0);
    EXIT_LOG_WITH_ERROR ("%d", result);
}

void SystemStatusOsObserver :: HandleTurnOff :: proc () const {
    int result = 0;
    ENTRY_LOG ();
    do {
        // Send action turn off to framework
        this->mParent->mContext.mFrameworkActionReqObj->turnOff(mDataItemId);
    } while (0);
    EXIT_LOG_WITH_ERROR ("%d", result);

void SystemStatusOsObserver::subscribe(const list<DataItemId>& l, IDataItemObserver* client,
                                       bool toRequestData)
{
    struct HandleSubscribeReq : public LocMsg {
        inline HandleSubscribeReq(SystemStatusOsObserver* parent,
                list<DataItemId>& l, IDataItemObserver* client, bool requestData) :
                mParent(parent), mClient(client),
                mDataItemSet(containerTransfer<list<DataItemId>, unordered_set<DataItemId>>(l)),
                mToRequestData(requestData) {}

        void proc() const {
            unordered_set<DataItemId> dataItemsToSubscribe(0);
            mParent->mDataItemToClients.add(mDataItemSet, {mClient}, &dataItemsToSubscribe);
            mParent->mClientToDataItems.add(mClient, mDataItemSet);

            mParent->sendCachedDataItems(mDataItemSet, mClient);

            // Send subscription set to framework
            if (nullptr != mParent->mContext.mSubscriptionObj && !dataItemsToSubscribe.empty()) {
                LOC_LOGD("Subscribe Request sent to framework for the following");
                mParent->logMe(dataItemsToSubscribe);

                if (mToRequestData) {
                    mParent->mContext.mSubscriptionObj->requestData(
                            containerTransfer<unordered_set<DataItemId>, list<DataItemId>>(
                                    std::move(dataItemsToSubscribe)),
                            mParent);
                } else {
                    mParent->mContext.mSubscriptionObj->subscribe(
                            containerTransfer<unordered_set<DataItemId>, list<DataItemId>>(
                                    std::move(dataItemsToSubscribe)),
                            mParent);
                }
            }
        }
        mutable SystemStatusOsObserver* mParent;
        IDataItemObserver* mClient;
        const unordered_set<DataItemId> mDataItemSet;
        bool mToRequestData;
    };

    if (l.empty() || nullptr == client) {
        LOC_LOGw("Data item set is empty or client is nullptr");
    } else {
        mContext.mMsgTask->sendMsg(
                new HandleSubscribeReq(this, (list<DataItemId>&)l, client, toRequestData));
    }
}

void SystemStatusOsObserver::updateSubscription(
        const list<DataItemId>& l, IDataItemObserver* client)
{
    struct HandleUpdateSubscriptionReq : public LocMsg {
        HandleUpdateSubscriptionReq(SystemStatusOsObserver* parent,
                                    list<DataItemId>& l, IDataItemObserver* client) :
                mParent(parent), mClient(client),
                mDataItemSet(containerTransfer<list<DataItemId>, unordered_set<DataItemId>>(l)) {}

        void proc() const {
            unordered_set<DataItemId> dataItemsToSubscribe(0);
            unordered_set<DataItemId> dataItemsToUnsubscribe(0);
            unordered_set<IDataItemObserver*> clients({mClient});
            // below removes clients from all entries keyed with the return of the
            // mClientToDataItems.update() call. If leaving an empty set of clients as the
            // result, the entire entry will be removed. dataItemsToUnsubscribe will be
            // populated to keep the keys of the removed entries.
            mParent->mDataItemToClients.trimOrRemove(
                    // this call updates <IDataItemObserver*, DataItemId> map; removes
                    // the DataItemId's that are not new to the clietn from mDataItemSet;
                    // and returns a set of mDataItemSet's that are no longer used by client.
                    // This unused set of mDataItemSet's is passed to trimOrRemove method of
                    // <DataItemId, IDataItemObserver*> map to remove the client from the
                    // corresponding entries, and gets a set of the entries that are
                    // removed from the <DataItemId, IDataItemObserver*> map as a result.
                    mParent->mClientToDataItems.update(mClient,
                                                       (unordered_set<DataItemId>&)mDataItemSet),
                    clients, &dataItemsToUnsubscribe, nullptr);
            // below adds mClient to <DataItemId, IDataItemObserver*> map, and populates
            // new keys added to that map, which are DataItemIds to be subscribed.
            mParent->mDataItemToClients.add(mDataItemSet, clients, &dataItemsToSubscribe);

            // Send First Response
            mParent->sendCachedDataItems(mDataItemSet, mClient);

            if (nullptr != mParent->mContext.mSubscriptionObj) {
                // Send subscription set to framework
                if (!dataItemsToSubscribe.empty()) {
                    LOC_LOGD("Subscribe Request sent to framework for the following");
                    mParent->logMe(dataItemsToSubscribe);

                    mParent->mContext.mSubscriptionObj->subscribe(
                            containerTransfer<unordered_set<DataItemId>, list<DataItemId>>(
                                    std::move(dataItemsToSubscribe)),
                            mParent);
                }

                // Send unsubscribe to framework
                if (!dataItemsToUnsubscribe.empty()) {
                    LOC_LOGD("Unsubscribe Request sent to framework for the following");
                    mParent->logMe(dataItemsToUnsubscribe);

                    mParent->mContext.mSubscriptionObj->unsubscribe(
                            containerTransfer<unordered_set<DataItemId>, list<DataItemId>>(
                                    std::move(dataItemsToUnsubscribe)),
                            mParent);
                }
            }
        }
        SystemStatusOsObserver* mParent;
        IDataItemObserver* mClient;
        unordered_set<DataItemId> mDataItemSet;
    };

    if (l.empty() || nullptr == client) {
        LOC_LOGw("Data item set is empty or client is nullptr");
    } else {
        mContext.mMsgTask->sendMsg(
                new HandleUpdateSubscriptionReq(this, (list<DataItemId>&)l, client));
    }
}

void SystemStatusOsObserver::unsubscribe(
        const list<DataItemId>& l, IDataItemObserver* client)
{
    struct HandleUnsubscribeReq : public LocMsg {
        HandleUnsubscribeReq(SystemStatusOsObserver* parent,
                list<DataItemId>& l, IDataItemObserver* client) :
                mParent(parent), mClient(client),
                mDataItemSet(containerTransfer<list<DataItemId>, unordered_set<DataItemId>>(l)) {}

        void proc() const {
            unordered_set<DataItemId> dataItemsUnusedByClient(0);
            unordered_set<IDataItemObserver*> clientToRemove(0);
            mParent->mClientToDataItems.trimOrRemove({mClient}, mDataItemSet,  &clientToRemove,
                                                     &dataItemsUnusedByClient);
            unordered_set<DataItemId> dataItemsToUnsubscribe(0);
            mParent->mDataItemToClients.trimOrRemove(dataItemsUnusedByClient, {mClient},
                                                     &dataItemsToUnsubscribe, nullptr);

            if (nullptr != mParent->mContext.mSubscriptionObj && !dataItemsToUnsubscribe.empty()) {
                LOC_LOGD("Unsubscribe Request sent to framework for the following data items");
                mParent->logMe(dataItemsToUnsubscribe);

                // Send unsubscribe to framework
                mParent->mContext.mSubscriptionObj->unsubscribe(
                        containerTransfer<unordered_set<DataItemId>, list<DataItemId>>(
                                  std::move(dataItemsToUnsubscribe)),
                        mParent);
            }
        }
        SystemStatusOsObserver* mParent;
        IDataItemObserver* mClient;
        unordered_set<DataItemId> mDataItemSet;
    };

    if (l.empty() || nullptr == client) {
        LOC_LOGw("Data item set is empty or client is nullptr");
    } else {
        mContext.mMsgTask->sendMsg(new HandleUnsubscribeReq(this, (list<DataItemId>&)l, client));
    }
}

void SystemStatusOsObserver::unsubscribeAll(IDataItemObserver* client)
{
    struct HandleUnsubscribeAllReq : public LocMsg {
        HandleUnsubscribeAllReq(SystemStatusOsObserver* parent,
                IDataItemObserver* client) :
                mParent(parent), mClient(client) {}

        void proc() const {
            unordered_set<DataItemId> diByClient = mParent->mClientToDataItems.getValSet(mClient);
            if (!diByClient.empty()) {
                unordered_set<DataItemId> dataItemsToUnsubscribe;
                mParent->mClientToDataItems.remove(mClient);
                mParent->mDataItemToClients.trimOrRemove(diByClient, {mClient},
                                                         &dataItemsToUnsubscribe, nullptr);

                if (!dataItemsToUnsubscribe.empty() &&
                    nullptr != mParent->mContext.mSubscriptionObj) {

                    LOC_LOGD("Unsubscribe Request sent to framework for the following data items");
                    mParent->logMe(dataItemsToUnsubscribe);

                    // Send unsubscribe to framework
                    mParent->mContext.mSubscriptionObj->unsubscribe(
                            containerTransfer<unordered_set<DataItemId>, list<DataItemId>>(
                                    std::move(dataItemsToUnsubscribe)),
                            mParent);
                }
            }
        }
        SystemStatusOsObserver* mParent;
        IDataItemObserver* mClient;
    };

    if (nullptr == client) {
        LOC_LOGw("Data item set is empty or client is nullptr");
    } else {
        mContext.mMsgTask->sendMsg(new HandleUnsubscribeAllReq(this, client));
    }

}

/******************************************************************************
 IDataItemSubscription Overrides
******************************************************************************/

void SystemStatusOsObserver :: subscribe (const list <DataItemId> & l, IDataItemObserver * client) {
    int result = 0;
    ENTRY_LOG ();
    do {
        if (mContext.mSubscriptionObj != NULL) {
            HandleSubscribeReq * msg = new  (nothrow) HandleSubscribeReq (this, l, client);
            mContext.mMsgTask->sendMsg (msg);
        }
        else {
            LOC_LOGE("%s:%d]: Subscription object is NULL", __func__, __LINE__);
            result = 1;
        }
    } while (0);
    EXIT_LOG_WITH_ERROR ("%d",result);
}

void SystemStatusOsObserver :: updateSubscription (const list <DataItemId> & l, IDataItemObserver * client) {
    int result = 0;
    ENTRY_LOG ();
    do {
        if (mContext.mSubscriptionObj != NULL) {
            mContext.mMsgTask->sendMsg (new  (nothrow) HandleUpdateSubscriptionReq (this, l, client));
        }
        else {
            LOC_LOGE("%s:%d]: Subscription object is NULL", __func__, __LINE__);
            result = 1;
        }
    } while (0);
    EXIT_LOG_WITH_ERROR ("%d",result);
}

void SystemStatusOsObserver :: requestData (const list <DataItemId> & l, IDataItemObserver * client) {
    int result = 0;
    ENTRY_LOG ();
    do {
        if (mContext.mSubscriptionObj != NULL) {
            mContext.mMsgTask->sendMsg (new  (nothrow) HandleRequestData (this, l, client));
        }
        else {
            LOC_LOGE("%s:%d]: Subscription object is NULL", __func__, __LINE__);
            result = 1;
        }
    } while (0);

    EXIT_LOG_WITH_ERROR ("%d",result);
}

void SystemStatusOsObserver :: unsubscribe (const list <DataItemId> & l, IDataItemObserver * client) {
    int result = 0;
    ENTRY_LOG ();
    do {
        if (mContext.mSubscriptionObj != NULL) {
            mContext.mMsgTask->sendMsg (new  (nothrow) HandleUnsubscribeReq (this, l, client));
        }
        else {
            LOC_LOGE("%s:%d]: Subscription object is NULL", __func__, __LINE__);
            result = 1;
        }
    } while (0);
    EXIT_LOG_WITH_ERROR ("%d",result);
}

void SystemStatusOsObserver :: unsubscribeAll (IDataItemObserver * client) {
    int result = 0;
    ENTRY_LOG ();
    do {
        if (mContext.mSubscriptionObj != NULL) {
            mContext.mMsgTask->sendMsg (new  (nothrow) HandleUnsubscribeAllReq (this, client));
        }
        else {
            LOC_LOGE("%s:%d]: Subscription object is NULL", __func__, __LINE__);
            result = 1;
        }
    } while (0);
    EXIT_LOG_WITH_ERROR ("%d",result);
}

/******************************************************************************
 IDataItemObserver Overrides
******************************************************************************/
void SystemStatusOsObserver::getName(string & name) {
    name = mAddress;
}

void SystemStatusOsObserver::notify(const std::list <IDataItemCore *> & dlist) {
    int result = 0;
    ENTRY_LOG ();
    do {
        list <IDataItemCore *> :: const_iterator it = dlist.begin ();
        list <IDataItemCore *> dataItemList;
        list <DataItemId> ids;
        LOC_LOGD("LocTech-Label :: SystemStatusOsObserver :: Data Items In");
        for (; it != dlist.end (); ++it) {
            if (*it != NULL) {
                string dv;
                (*it)->stringify(dv);
                LOC_LOGD("LocTech-Value :: Data Item Value: %s", dv.c_str ());
                IDataItemCore * dataitem = DataItemsFactoryProxy::createNewDataItem((*it)->getId());
                BREAK_IF_ZERO (2, dataitem);
                // Copy contents into the newly created data item
                dataitem->copy(*it);
                dataItemList.push_back(dataitem);
                ids.push_back((*it)->getId());
            }
        }
        mContext.mMsgTask->sendMsg(new (nothrow) HandleNotify (this, dataItemList));
    } while  (0);
    EXIT_LOG_WITH_ERROR ("%d", result);

void SystemStatusOsObserver::notify(const list<IDataItemCore*>& dlist)
{
    struct HandleNotify : public LocMsg {
        HandleNotify(SystemStatusOsObserver* parent, vector<IDataItemCore*>& v) :
                mParent(parent), mDiVec(std::move(v)) {}

        inline virtual ~HandleNotify() {
            for (auto item : mDiVec) {
                delete item;
            }
        }

        void proc() const {
            // Update Cache with received data items and prepare
            // list of data items to be sent.
            unordered_set<DataItemId> dataItemIdsToBeSent(0);
            for (auto item : mDiVec) {
                if (mParent->updateCache(item)) {
                    dataItemIdsToBeSent.insert(item->getId());
                }
            }

            // Send data item to all subscribed clients
            unordered_set<IDataItemObserver*> clientSet(0);
            for (auto each : dataItemIdsToBeSent) {
                auto clients = mParent->mDataItemToClients.getValSetPtr(each);
                if (nullptr != clients) {
                    clientSet.insert(clients->begin(), clients->end());
                }
            }

            for (auto client : clientSet) {
                unordered_set<DataItemId> dataItemIdsForThisClient(
                        mParent->mClientToDataItems.getValSet(client));
                for (auto id : dataItemIdsForThisClient) {
                    if (dataItemIdsToBeSent.find(id) == dataItemIdsToBeSent.end()) {
                        dataItemIdsForThisClient.erase(id);
                    }
                }

                mParent->sendCachedDataItems(dataItemIdsForThisClient, client);
            }
        }
        SystemStatusOsObserver* mParent;
        const vector<IDataItemCore*> mDiVec;
    };

    if (!dlist.empty()) {
        vector<IDataItemCore*> dataItemVec(dlist.size());

        for (auto each : dlist) {
            IF_LOC_LOGD {
                string dv;
                each->stringify(dv);
                LOC_LOGD("notify: DataItem In Value:%s", dv.c_str());
            }

            IDataItemCore* di = DataItemsFactoryProxy::createNewDataItem(each->getId());
            if (nullptr == di) {
                LOC_LOGw("Unable to create dataitem:%d", each->getId());
                continue;
            }

            // Copy contents into the newly created data item
            di->copy(each);

            // add this dataitem if updated from last one
            dataItemVec.push_back(di);
        }

        if (!dataItemVec.empty()) {
            mContext.mMsgTask->sendMsg(new HandleNotify(this, dataItemVec));
        }
    }

}

/******************************************************************************
 IFrameworkActionReq Overrides
******************************************************************************/

void SystemStatusOsObserver :: turnOn (DataItemId dit, int timeOut) {
    int result = 0;
    ENTRY_LOG ();
    do {
        if (mContext.mFrameworkActionReqObj != NULL) {
            // Check if data item exists in mActiveRequestCount
            map <DataItemId, int> :: iterator citer = mActiveRequestCount.find (dit);
            if (citer == mActiveRequestCount.end ()) {
                // Data item not found in map
                // Add reference count as 1 and add dataitem to map
                pair <DataItemId, int> cpair (dit, 1);
                mActiveRequestCount.insert (cpair);
                LOC_LOGD("Sending turnOn request");
                // Send action turn on to framework
                mContext.mMsgTask->sendMsg (new  (nothrow) HandleTurnOn (this, dit, timeOut));
            } else {
                // Found in map, update reference count
                citer->second++;
                LOC_LOGD("HandleTurnOn - Data item:%d Num_refs:%d",dit,citer->second);

void SystemStatusOsObserver::turnOn(DataItemId dit, int timeOut)
{
    if (nullptr == mContext.mFrameworkActionReqObj) {
        LOC_LOGE("%s:%d]: Framework action request object is NULL", __func__, __LINE__);
        return;
    }

    // Check if data item exists in mActiveRequestCount
    DataItemIdToInt::iterator citer = mActiveRequestCount.find(dit);
    if (citer == mActiveRequestCount.end()) {
        // Data item not found in map
        // Add reference count as 1 and add dataitem to map
        pair<DataItemId, int> cpair(dit, 1);
        mActiveRequestCount.insert(cpair);
        LOC_LOGD("Sending turnOn request");

        // Send action turn on to framework
        struct HandleTurnOnMsg : public LocMsg {
            HandleTurnOnMsg(IFrameworkActionReq* framework,
                    DataItemId dit, int timeOut) :
                    mFrameworkActionReqObj(framework), mDataItemId(dit), mTimeOut(timeOut) {}
            virtual ~HandleTurnOnMsg() {}
            void proc() const {
                mFrameworkActionReqObj->turnOn(mDataItemId, mTimeOut);

            }
        }
        else {
            LOC_LOGE("%s:%d]: Framework action request object is NULL", __func__, __LINE__);
            result = 1;
        }
    } while (0);

    EXIT_LOG_WITH_ERROR ("%d", result);
}


void SystemStatusOsObserver :: turnOff (DataItemId dit) {
    int result = 0;
    ENTRY_LOG ();
    do {
        if (mContext.mFrameworkActionReqObj != NULL) {
            // Check if data item exists in mActiveRequestCount
            map <DataItemId, int> :: iterator citer = mActiveRequestCount.find (dit);
            if (citer != mActiveRequestCount.end ()) {
                citer->second--;
                LOC_LOGD("HandleTurnOff - Data item:%d Remaining Num_refs:%d",dit,citer->second);

                if(citer->second == 0) {
                    LOC_LOGD("Sending turnOff request");
                    // if this was last reference, remove item from map and turn off module
                    mActiveRequestCount.erase(citer);
                    // Send action turn off to framework
                    mContext.mMsgTask->sendMsg (new  (nothrow) HandleTurnOff (this, dit));

    // Check if data item exists in mActiveRequestCount
    DataItemIdToInt::iterator citer = mActiveRequestCount.find(dit);
    if (citer != mActiveRequestCount.end()) {
        // found
        citer->second--;
        LOC_LOGD("turnOff - Data item:%d Remaining:%d", dit, citer->second);
        if(citer->second == 0) {
            // if this was last reference, remove item from map and turn off module
            mActiveRequestCount.erase(citer);

            // Send action turn off to framework
            struct HandleTurnOffMsg : public LocMsg {
                HandleTurnOffMsg(IFrameworkActionReq* framework, DataItemId dit) :
                    mFrameworkActionReqObj(framework), mDataItemId(dit) {}
                virtual ~HandleTurnOffMsg() {}
                void proc() const {
                    mFrameworkActionReqObj->turnOff(mDataItemId);

                }
            } else {
                // Not found in map
                LOC_LOGD ("Data item id %d not found in FrameworkModuleMap",dit);
            }
        }
        else {
            LOC_LOGE("%s:%d]: Framework action request object is NULL", __func__, __LINE__);
            result = 1;
        }
    } while (0);
    EXIT_LOG_WITH_ERROR ("%d", result);
}


/******************************************************************************
 Helpers
******************************************************************************/
void SystemStatusOsObserver :: logMe (const list <DataItemId> & l) {
    list <DataItemId> :: const_iterator it = l.begin ();
    for (;it != l.end (); ++it) {
        LOC_LOGD ("DataItem %d",*it);
    }
}

int SystemStatusOsObserver :: sendFirstResponse (const list <DataItemId> & l, IDataItemObserver * to) {
    int result = 0;
    ENTRY_LOG ();
    do {
        if (l.empty ()) {
            LOC_LOGV("list is empty. Nothing to do. Exiting");
            result = 0;
            break;
        }

        string clientName;
        to->getName (clientName);
        LOC_LOGD ("First response sent for the following data items To Client: %s", clientName.c_str());

        list <IDataItemCore *> dataItems;
        list <DataItemId> :: const_iterator diditer = l.begin ();
        for (; diditer != l.end (); ++diditer) {
            map <DataItemId, IDataItemCore*> :: const_iterator citer = mDataItemCache.find (*diditer);
            if (citer != mDataItemCache.end ()) {
                string dv;
                IDataItemCore * di = citer->second;
                di->stringify (dv);
                LOC_LOGD ("LocTech-Value :: Data Item: %s", dv.c_str ());
                dataItems.push_back (citer->second);
            }
        }
        if (dataItems.empty ()) {
            LOC_LOGV("No items to notify. Nothing to do. Exiting");
            result = 0;
            break;
        }

        // Notify Client
        to->notify (dataItems);

    } while (0);
    EXIT_LOG_WITH_ERROR ("%d", result);
    return result;
}

int SystemStatusOsObserver :: sendCachedDataItems (const list <DataItemId> & l, IDataItemObserver * to) {
    int result = 0;
    ENTRY_LOG ();
    do {
        list <IDataItemCore *> dataItems;
        list <DataItemId> :: const_iterator it = l.begin ();
        string clientName;
        to->getName (clientName);
        LOC_LOGD ("LocTech-Value :: To Client: %s", clientName.c_str ());
        for (; it != l.end (); ++it) {
            string dv;
            IDataItemCore * di = this->mDataItemCache [ (*it) ];
            di->stringify (dv);
            LOC_LOGI("LocTech-Value :: Data Item: %s >> %s", dv.c_str(), clientName.c_str());
            dataItems.push_back (di);
        }

        to->notify (dataItems);

    } while (0);
    EXIT_LOG_WITH_ERROR ("%d", result);
    return result;
}

int SystemStatusOsObserver :: updateCache (IDataItemCore * d, bool &dataItemUpdated) {
    int result = 0;
    ENTRY_LOG ();
    do {
        BREAK_IF_ZERO (1, d);
        // Check if data item exists in cache
        map <DataItemId, IDataItemCore*> :: iterator citer = mDataItemCache.find (d->getId ());
        if (citer == mDataItemCache.end ()) {
            // New data item; not found in cache
            IDataItemCore * dataitem = DataItemsFactoryProxy::createNewDataItem(d->getId());
            BREAK_IF_ZERO (2, dataitem);
            // Copy the contents of the data item
            dataitem->copy (d);
            pair <DataItemId, IDataItemCore*> cpair (d->getId (), dataitem);
            // Insert in mDataItemCache
            mDataItemCache.insert (cpair);
            dataItemUpdated = true;
        } else {
            // Found in cache; Update cache if necessary
            BREAK_IF_NON_ZERO(3, citer->second->copy (d, &dataItemUpdated));
        }

        if (dataItemUpdated) {
            LOC_LOGV("DataItem:%d updated:%d", d->getId (), dataItemUpdated);

#ifdef USE_GLIB
bool SystemStatusOsObserver::connectBackhaul()
{
    bool result = false;

    if (mContext.mFrameworkActionReqObj != NULL) {
        struct HandleConnectBackhaul : public LocMsg {
            HandleConnectBackhaul(IFrameworkActionReq* fwkActReq) :
                    mFwkActionReqObj(fwkActReq) {}
            virtual ~HandleConnectBackhaul() {}
            void proc() const {
                LOC_LOGD("HandleConnectBackhaul");
                mFwkActionReqObj->connectBackhaul();
            }
            IFrameworkActionReq* mFwkActionReqObj;
        };
        mContext.mMsgTask->sendMsg(
                new (nothrow) HandleConnectBackhaul(mContext.mFrameworkActionReqObj));
        result = true;
    }
    else {
        ++mBackHaulConnectReqCount;
        LOC_LOGE("Framework action request object is NULL.Caching connect request: %d",
                        mBackHaulConnectReqCount);
        result = false;
    }
    return result;

}

bool SystemStatusOsObserver::disconnectBackhaul()
{
    bool result = false;

    if (mContext.mFrameworkActionReqObj != NULL) {
        struct HandleDisconnectBackhaul : public LocMsg {
            HandleDisconnectBackhaul(IFrameworkActionReq* fwkActReq) :
                    mFwkActionReqObj(fwkActReq) {}
            virtual ~HandleDisconnectBackhaul() {}
            void proc() const {
                LOC_LOGD("HandleDisconnectBackhaul");
                mFwkActionReqObj->disconnectBackhaul();
            }
            IFrameworkActionReq* mFwkActionReqObj;
        };
        mContext.mMsgTask->sendMsg(
                new (nothrow) HandleDisconnectBackhaul(mContext.mFrameworkActionReqObj));
    }
    else {
        if (mBackHaulConnectReqCount > 0) {
            --mBackHaulConnectReqCount;
        }
        LOC_LOGE("Framework action request object is NULL.Caching disconnect request: %d",
                        mBackHaulConnectReqCount);
        result = false;
    }
    return result;
}
#endif
/******************************************************************************
 Helpers
******************************************************************************/
void SystemStatusOsObserver::sendCachedDataItems(
        const unordered_set<DataItemId>& s, IDataItemObserver* to)
{
    if (nullptr == to) {
        LOC_LOGv("client pointer is NULL.");
    } else {
        string clientName;
        to->getName(clientName);
        list<IDataItemCore*> dataItems(0);

        for (auto each : s) {
            auto citer = mDataItemCache.find(each);
            if (citer != mDataItemCache.end()) {
                string dv;
                citer->second->stringify(dv);
                LOC_LOGI("DataItem: %s >> %s", dv.c_str(), clientName.c_str());
                dataItems.push_front(citer->second);
            }
        }

        if (dataItems.empty()) {
            LOC_LOGv("No items to notify.");
        } else {
            to->notify(dataItems);
        }
    }
}

bool SystemStatusOsObserver::updateCache(IDataItemCore* d)
{
    bool dataItemUpdated = false;

    // Request systemstatus to record this dataitem in its cache
    // if the return is false, it means that SystemStatus is not
    // handling it, so SystemStatusOsObserver also doesn't.
    // So it has to be true to proceed.
    if (nullptr != d && mSystemStatus->eventDataItemNotify(d)) {
        auto citer = mDataItemCache.find(d->getId());
        if (citer == mDataItemCache.end()) {
            // New data item; not found in cache
            IDataItemCore* dataitem = DataItemsFactoryProxy::createNewDataItem(d->getId());
            if (nullptr != dataitem) {
                // Copy the contents of the data item
                dataitem->copy(d);
                // Insert in mDataItemCache
                mDataItemCache.insert(std::make_pair(d->getId(), dataitem));
                dataItemUpdated = true;
            }
        } else {
            // Found in cache; Update cache if necessary
            citer->second->copy(d, &dataItemUpdated);
        }

        if (dataItemUpdated) {
            LOC_LOGV("DataItem:%d updated:%d", d->getId(), dataItemUpdated);

        }
    } while (0);


    EXIT_LOG_WITH_ERROR ("%d", result);
    return result;

    return dataItemUpdated;

}

} // namespace loc_core

