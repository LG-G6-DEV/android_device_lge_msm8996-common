#
# Vendor Properties for LG MSM8996
#

# LTE, CDMA, GSM/WCDMA
PRODUCT_PROPERTY_OVERRIDES += \
    ro.telephony.default_network=9 \
    persist.radio.mode_pref_nv10=1 \
    persist.radio.add_power_save=1

# Art
PRODUCT_PROPERTY_OVERRIDES += \
    ro.sys.fw.dex2oat_thread_count=4

# Audio
PRODUCT_PROPERTY_OVERRIDES += \
    af.fast_track_multiplier=1 \
    audio.deep_buffer.media=true \
    audio.offload.min.duration.secs=15 \
    audio.offload.video=true \
    persist.vendor.audio.speaker.prot.enable=true \
    persist.audio.dual_audio=ON \
    persist.audio.handset_rx_type=DEFAULT \
    persist.audio.twin_headset=DISABLE \
    persist.audio.twin_headset_on=0 \
    persist.audio.nsenabled=ON \
    persist.audio.voice.clarity=off \
    persist.vendor.audio.fluence.speaker=true \
    persist.vendor.audio.fluence.voicecall=true \
    persist.vendor.audio.fluence.voicerec=false \
    persist.vendor.bt.enable.splita2dp=false \
    ro.config.vc_call_vol_steps=7 \
    ro.af.client_heap_size_kbyte=7168 \
    ro.vendor.audio.sdk.fluencetype=fluence \
    ro.vendor.audio.sdk.ssr=false \
    vendor.audio.dolby.ds2.enabled=false \
    vendor.audio.dolby.ds2.hardbypass=false \
    vendor.audio.flac.sw.decoder.24bit=true \
    vendor.audio_hal.period_size=192 \
    vendor.audio.hw.aac.encoder=true \
    vendor.audio.noisy.broadcast.delay=600 \
    vendor.audio.offload.buffer.size.kb=64 \
    vendor.audio.offload.gapless.enabled=true \
    vendor.audio.offload.multiaac.enable=true \
    vendor.audio.offload.multiple.enabled=false \
    vendor.audio.offload.passthrough=false \
    vendor.audio.offload.pstimeout.secs=3 \
    vendor.audio.offload.track.enable=true \
    vendor.audio.parser.ip.buffer.size=262144 \
    vendor.audio.safx.pbe.enabled=true \
    vendor.audio.tunnel.encode=false \
    vendor.audio.use.sw.alac.decoder=true \
    vendor.audio.use.sw.ape.decoder=true \
    vendor.voice.path.for.pcm.voip=false


# Bluetooth
PRODUCT_PROPERTY_OVERRIDES += \
    ro.bt.bdaddr_path=/data/misc/bluetooth/bdaddr \
    qcom.bluetooth.soc=rome \
    bluetooth.chip.vendor=brcm \
    bluetooth.pan=true \
    persist.bluetooth.avrcpversion=avrcp15

# Camera
PRODUCT_PROPERTY_OVERRIDES += \
    vendor.camera.aux.packagelist=all,com.android.camera2,com.google.android.GoogleCameraWide \
    persist.camera.expose.aux=1 \
    ro.camera.notify_nfc=1 \
    vidc.debug.perf.mode=2 \
    vidc.enc.dcvs.extra-buff-count=2 \
    persist.audio.camcorder.stereo=true \
    persist.camera.preview.ubwc=0 \
    persist.camera.video.ubwc=0

# CNE and DPM
PRODUCT_PROPERTY_OVERRIDES += \
    persist.cne.feature=1 \
    persist.dpm.feature=0

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
    ro.use_data_netmgrd=true \
    persist.data.df.dev_name=rmnet_usb0 \
    persist.data.df.iwlan_mux=9 \
    persist.data.iwlan.enable=true \
    persist.data.mode=concurrent \
    persist.data.netmgrd.qos.enable=true

# Display
PRODUCT_PROPERTY_OVERRIDES += \
    ro.qualcomm.cabl=0 \
    ro.sf.lcd_density=560

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
    debug.gralloc.enable_fb_ubwc=1 \
    dev.pm.dyn_samplingrate=1 \
    persist.demo.hdmirotationlock=false \
    persist.sys.wfd.virtual=0 \
    sdm.perf_hint_window=50 \
    persist.hwc.enable_vds=1 \
    sdm.debug.disable_rotator_split=1 \
    debug.composition.type=gpu \
    debug.egl.hw=1 \
    debug.egl.profiler=1 \
    debug.performance.tuning=1 \
    debug.sf.hw=1 \
    debug.sf.latch_unsignaled=1 \
    hw3d.force=1 \
    hwui.disable_vsync=false \
    hwui.render_dirty_regions=false \
    ro.config.disable.hw_accel=false \
    ro.fb.mode=1 \
    ro.product.gpu.driver=1 \
    ro.sf.compbypass.enable=0

# HWUI
PRODUCT_PROPERTY_OVERRIDES += \
    ro.hwui.texture_cache_size=96 \
    ro.hwui.layer_cache_size=64 \
    ro.hwui.r_buffer_cache_size=12 \
    ro.hwui.path_cache_size=39 \
    ro.hwui.gradient_cache_size=1 \
    ro.hwui.drop_shadow_cache_size=7 \
    ro.hwui.texture_cache_flushrate=0.4 \
    ro.hwui.text_small_cache_width=2048 \
    ro.hwui.text_small_cache_height=2048 \
    ro.hwui.text_large_cache_width=3072 \
    ro.hwui.text_large_cache_height=2048

# OpenGLES
PRODUCT_PROPERTY_OVERRIDES += \
    ro.opengles.version=196610

# Perf
PRODUCT_PROPERTY_OVERRIDES += \
    ro.am.reschedule_service=true \
    ro.min_freq_0=307200 \
    ro.min_freq_4=307200 \
    ro.sys.fw.bg_apps_limit=60 \
    ro.vendor.extension_library=libqti-perfd-client.so

# RIL
PRODUCT_PROPERTY_OVERRIDES += \
    rild.libpath=/vendor/lib64/libril-qc-qmi-1.so \
    vendor.rild.libpath=/vendor/lib64/libril-qc-qmi-1.so \
    ril.subscription.types=NV,RUIM \
    DEVICE_PROVISIONED=1 \
    persist.data.qmi.adb_logmask=0 \
    persist.net.doxlat=true \
    persist.radio.apm_sim_not_pwdn=1 \
    persist.radio.custom_ecc=1 \
    persist.radio.force_on_dc=true \
    persist.radio.rat_on=combine \
    persist.radio.redir_party_num=1 \
    persist.radio.sib16_support=1 \
    ro.telephony.call_ring.multiple=false

# Radio - Data/RMNet
PRODUCT_PROPERTY_OVERRIDES += \
    persist.data.df.agg.dl_pkt=10 \
    persist.data.df.agg.dl_size=4096 \
    persist.data.df.dev_name=rmnet_usb0 \
    persist.data.df.dl_mode=5 \
    persist.data.df.iwlan_mux=9 \
    persist.data.df.mux_count=8 \
    persist.data.df.ul_mode=5 \
    persist.data.iwlan.enable=true \
    persist.data.qmi.adb_logmask=0 \
    persist.data.wda.enable=true \
    persist.rmnet.data.enable=true

# Radio - IMS
PRODUCT_PROPERTY_OVERRIDES += \
    persist.dbg.volte_avail_ovr=1 \
    persist.dbg.vt_avail_ovr=1 \
    persist.radio.NO_STAPA=1 \
    persist.radio.VT_HYBRID_ENABLE=1

# Memory optimizations
PRODUCT_PROPERTY_OVERRIDES += \
    ro.vendor.qti.sys.fw.bservice_enable=true

# Sensors
PRODUCT_PROPERTY_OVERRIDES += \
    persist.debug.sensors.hal=e \
    debug.qualcomm.sns.daemon=i \
    debug.qualcomm.sns.libsensor1=i \
    persist.sensors.lgpickup_en=true \
    persist.sensors.mag_filter_size=8 \
    persist.sensors.knock_delay=700 \
    persist.sensors.pocket_delay=350 \
    persist.sensors.wul_multilevel=6 \
    persist.sensors.wul_thresh0=2 \
    persist.sensors.wul_thresh1=10 \
    persist.sensors.wul_thresh2=15 \
    persist.sensors.wul_thresh3=1500 \
    persist.sensors.wul_thresh4=3100 \
    persist.sensors.wul_thresh5=10000 \
    persist.sensors.wul_delay=3000 \
    persist.sensors.onhand.en=0


# Tethering
PRODUCT_PROPERTY_OVERRIDES += \
    net.tethering.noprovisioning=true

# Time services
PRODUCT_PROPERTY_OVERRIDES += \
    persist.timed.enable=true \
    persist.delta_time.enable=true

# WiFi
PRODUCT_PROPERTY_OVERRIDES += \
    wifi.interface=wlan0

#enable Apical AD
PRODUCT_PROPERTY_OVERRIDES += \
    ro.qcom.ad=1 \
    ro.qcom.ad.sensortype=3
