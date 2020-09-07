#
# Vendor Properties for LG MSM8996
#

# LTE, CDMA, GSM/WCDMA
PRODUCT_PROPERTY_OVERRIDES += \
    ro.telephony.default_network=9 \
    persist.radio.mode_pref_nv10=1 \
    persist.radio.add_power_save=1

# Audio
PRODUCT_PROPERTY_OVERRIDES += \
    af.fast_track_multiplier=1 \
    audio.deep_buffer.media=true \
    audio.offload.min.duration.secs=30 \
    audio.offload.video=true \
    persist.audio.handset_rx_type=DEFAULT \
    persist.audio.twin_headset=DISABLE \
    persist.audio.nsenabled=ON \
    persist.audio.voice.clarity=off \
    persist.vendor.audio.fluence.speaker=true \
    persist.vendor.audio.fluence.voicecall=true \
    persist.vendor.audio.fluence.voicerec=false \
    persist.vendor.audio.speaker.prot.enable=true \
    ro.af.client_heap_size_kbyte=7168 \
    ro.config.media_vol_steps=25 \
    ro.config.vc_call_vol_steps=7 \
    ro.vendor.audio.sdk.fluencetype=nxp \
    ro.vendor.audio.sdk.ssr=false \
    vendor.audio.dolby.ds2.enabled=false \
    vendor.audio.dolby.ds2.hardbypass=false \
    vendor.audio.flac.sw.decoder.24bit=true \
    vendor.audio_hal.period_size=480 \
    vendor.audio.hw.aac.encoder=false \
    vendor.audio.offload.buffer.size.kb=64 \
    vendor.audio.offload.gapless.enabled=true \
    vendor.audio.offload.multiaac.enable=true \
    vendor.audio.offload.multiple.enabled=false \
    vendor.audio.offload.passthrough=false \
    vendor.audio.offload.pstimeout.secs=3 \
    vendor.audio.offload.track.enable=false \
    vendor.audio.parser.ip.buffer.size=262144 \
    vendor.audio.safx.pbe.enabled=false \
    vendor.audio.tunnel.encode=false \
    vendor.audio.use.sw.alac.decoder=true \
    vendor.audio.use.sw.ape.decoder=true \
    vendor.voice.path.for.pcm.voip=false

# Audio - LGE
PRODUCT_PROPERTY_OVERRIDES += \
    persist.vendor.lge.audio.nsenabled=ON \
    persist.vendor.lge.audio.voice.clarity=off \
    persist.vendor.lge.audio.handset_rx_type=DEFAULT \
    vendor.lge.audio.hifi_rec.normal_gain=30 \
    vendor.lge.audio.hifi_rec.normal_lcf=75 \
    vendor.lge.audio.hifi_rec.normal_lmt=-3 \
    vendor.lge.audio.hifi_rec.concert_gain=-150 \
    vendor.lge.audio.hifi_rec.concert_lcf=0 \
    vendor.lge.audio.hifi_rec.concert_lmt=0 \
    vendor.lge.audio.hifi_rec.offset_gain=37

# Bluetooth
PRODUCT_PROPERTY_OVERRIDES += \
    ro.bt.bdaddr_path=/data/misc/bluetooth/bdaddr \
    vendor.bluetooth.soc=rome \
    bt.max.hfpclient.connections=1 \
    bluetooth.chip.vendor=brcm

# Camera
PRODUCT_PROPERTY_OVERRIDES += \
    Camera.no_navigation_bar=true \
    persist.camera.expose.aux=1 \
    ro.camera.notify_nfc=1 \
    persist.audio.camcorder.stereo=true \
    persist.camera.camera2=true \
    persist.camera.is_type=3 \
    persist.camera.preview.ubwc=0 \
    persist.camera.video.ubwc=0 \
    camera.disable_zsl_mode=1 \
    persist.camera.zsl.mode=0 \
    media.settings.xml=/vendor/etc/media_profiles_V1_0.xml

# CNE
PRODUCT_PROPERTY_OVERRIDES += \
    persist.vendor.cne.feature=1

# DPM
PRODUCT_PROPERTY_OVERRIDES += \
    persist.vendor.dpm.feature=5

# Dalvik VM
PRODUCT_PROPERTY_OVERRIDES += \
    dalvik.vm.heapstartsize=16m \
    dalvik.vm.heapsize=512m \
    dalvik.vm.heaptargetutilization=0.75 \
    dalvik.vm.heapminfree=4m \
    dalvik.vm.heapmaxfree=8m \
    dalvik.vm.heapgrowthlimit=256m

# Data modules
PRODUCT_PROPERTY_OVERRIDES += \
    persist.data.iwlan.enable=true \
    persist.data.mode=concurrent \
    persist.data.netmgrd.qos.enable=true \
    ro.vendor.use_data_netmgrd=true

# Display (Qualcomm Assertive Display)
PRODUCT_PROPERTY_OVERRIDES += \
    ro.qcom.ad=1 \
    ro.qcom.ad.sensortype=3 \
    ro.vendor.display.cabl=2

# Factory Reset Protection (FRP)
PRODUCT_PROPERTY_OVERRIDES += \
    ro.frp.pst=/dev/block/platform/soc/624000.ufshc/by-name/persistent

# GPS
PRODUCT_PROPERTY_OVERRIDES += \
    persist.gps.qc_nlp_in_use=1 \
    persist.loc.nlp_name=com.qualcomm.location \
    ro.gps.agps_provider=1

# Graphics
PRODUCT_PROPERTY_OVERRIDES += \
    debug.egl.hw=1 \
    debug.sf.enable_hwc_vds=1 \
    debug.sf.hw=1 \
    dev.pm.dyn_samplingrate=1 \
    persist.debug.wfd.enable=1 \
    persist.demo.hdmirotationlock=false \
    persist.hwc.enable_vds=1 \
    persist.sys.wfd.nohdcp=1 \
    persist.sys.wfd.virtual=0 \
    ro.persist.qcapb=1 \
    vendor.display.disable_rotator_split=1 \
    vendor.display.disable_skip_validate=1 \
    vendor.display.enable_default_color_mode=1 \
    vendor.display.perf_hint_window=50 \
    vendor.gralloc.disable_wb_ubwc=1 \
    persist.sys.sf.color_saturation=1.1 \
    debug.hwui.renderer=skiagl

# Graphics (OpenGLES)
PRODUCT_PROPERTY_OVERRIDES += \
   ro.opengles.version=196610

# HDR
PRODUCT_PROPERTY_OVERRIDES += \
ro.qcom.hdr.config=/system/vendor/etc/hdr_tm_config.xml

# Media
PRODUCT_PROPERTY_OVERRIDES += \
   vidc.debug.perf.mode=2 \
   vidc.enc.dcvs.extra-buff-count=2

# IMS / VoLTE
PRODUCT_PROPERTY_OVERRIDES += \
   persist.dbg.volte_avail_ovr=1 \
   persist.dbg.vt_avail_ovr=1 \
   persist.dbg.wfc_avail_ovr=1 \
   persist.radio.VT_ENABLE=1 \
   persist.radio.VT_HYBRID_ENABLE=1 \
   persist.vendor.qti.telephony.vt_cam_interface=2

# Perf
PRODUCT_PROPERTY_OVERRIDES += \
   ro.vendor.extension_library=libqti-perfd-client.so

# RIL
PRODUCT_PROPERTY_OVERRIDES += \
    DEVICE_PROVISIONED=1 \
    persist.data.qmi.adb_logmask=0 \
    persist.net.doxlat=true \
    persist.radio.apm_sim_not_pwdn=1 \
    persist.radio.csvt.enabled=false \
    persist.radio.REVERSE_QMI=0 \
    persist.radio.ROTATION_ENABLE=1 \
    persist.rcs.supported=1 \
    persist.vendor.radio.aosp_usr_pref_sel=true \
    persist.vendor.radio.cs_srv_type=1 \
    persist.vendor.radio.custom_ecc=1 \
    persist.vendor.radio.data_ltd_sys_ind=1 \
    persist.vendor.radio.facnotsup_as_nonw=1 \
    persist.vendor.radio.force_on_dc=true \
    persist.vendor.radio.ignore_dom_time=5 \
    persist.vendor.radio.mt_sms_ack=20 \
    persist.vendor.radio.rat_on=combine \
    persist.vendor.radio.redir_party_num=1 \
    persist.vendor.radio.sib16_support=1 \
    ril.subscription.types=NV,RUIM \
    rild.libpath=/vendor/lib64/libril-qc-qmi-1.so \
    ro.telephony.call_ring.multiple=false \
    ro.telephony.use_old_mnc_mcc_format=true \

# Sensors
PRODUCT_PROPERTY_OVERRIDES += \
    ro.qti.sensors.dev_ori=false \
    ro.qti.sensors.pmd=false \
    ro.qti.sensors.sta_detect=false \
    ro.qti.sensors.mot_detect=false \
	persist.vendor.debug.sensors.hal=i \
	debug.vendor.sns.daemon=i \
	debug.vendor.sns.libsensor1=e \
	persist.vendor.lge.sensors.mag_filter_size=8 \
	persist.vendor.lge.sensors.knock_delay=1000 \
	persist.vendor.lge.sensors.pocket_delay=1000 \
	persist.vendor.lge.sensors.wul_delay=3000 \
	persist.vendor.lge.sensors.wul_multilevel=6 \
	persist.vendor.lge.sensors.wul_thresh0=2 \
	persist.vendor.lge.sensors.wul_thresh1=10 \
	persist.vendor.lge.sensors.wul_thresh2=15 \
	persist.vendor.lge.sensors.wul_thresh3=1500 \
	persist.vendor.lge.sensors.wul_thresh4=3100 \
	persist.vendor.lge.sensors.wul_thresh5=10000 \
	persist.vendor.lge.sensors.lgpickup=true

# Settings app
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.fflag.override.settings_network_and_internet_v2=true

# Surfaceflinger
PRODUCT_PROPERTY_OVERRIDES += \
    debug.sf.early_app_phase_offset_ns=1500000 \
    debug.sf.early_gl_app_phase_offset_ns=15000000 \
    debug.sf.early_gl_phase_offset_ns=3000000 \
    debug.sf.early_phase_offset_ns=1500000

# Tethering
PRODUCT_PROPERTY_OVERRIDES += \
    net.tethering.noprovisioning=true

# Timeservice
PRODUCT_PROPERTY_OVERRIDES += \
    persist.timed.enable=true

# Voice assistant
PRODUCT_PROPERTY_OVERRIDES += \
    ro.opa.eligible_device=true

# WiFi
PRODUCT_PROPERTY_OVERRIDES += \
    wifi.interface=wlan0 \
    wifi.direct.interface=p2p-dev-wlan0