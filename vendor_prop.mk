#
# Vendor Properties for LG MSM8996
#

# LTE, CDMA, GSM/WCDMA
PRODUCT_PROPERTY_OVERRIDES += \
    persist.radio.mode_pref_nv10=1 \
    persist.radio.add_power_save=1

# Art
PRODUCT_PROPERTY_OVERRIDES += \
    ro.sys.fw.dex2oat_thread_count=4

# Audio
PRODUCT_PROPERTY_OVERRIDES += \
    af.fast_track_multiplier=1 \
    audio.deep_buffer.media=true \
    audio.heap.size.multiplier=7 \
    audio.offload.min.duration.secs=30 \
    audio.offload.video=false \
    persist.audio.dual_audio=ON \
    persist.audio.handset_rx_type=DEFAULT \
    persist.audio.twin_headset=DISABLE \
    persist.audio.twin_headset_on=0 \
    persist.audio.nsenabled=ON \
    persist.audio.voice.clarity=off \
    persist.audio.ssr.3mic=false \
    persist.vendor.audio.fluence.audiorec=false \
    persist.vendor.audio.fluence.speaker=true \
    persist.vendor.audio.fluence.voicecall=true \
    persist.vendor.audio.fluence.voicerec=false \
    persist.vendor.audio.speaker.prot.enable=true \
    persist.vendor.bt.enable.splita2dp=false \
    ro.af.client_heap_size_kbyte=7168 \
    ro.config.media_vol_steps=25 \
    ro.config.vc_call_vol_steps=7 \
    ro.vendor.audio.sdk.fluencetype=fluence \
    ro.vendor.audio.sdk.ssr=false \
    vendor.audio.dolby.ds2.enabled=false \
    vendor.audio.dolby.ds2.hardbypass=false \
    vendor.audio.flac.sw.decoder.24bit=true \
    vendor.audio_hal.period_size=192 \
    vendor.audio.hw.aac.encoder=false \
    vendor.audio.offload.buffer.size.kb=64 \
    vendor.audio.offload.gapless.enabled=true \
    vendor.audio.offload.multiaac.enable=true \
    vendor.audio.offload.multiple.enabled=false \
    vendor.audio.offload.passthrough=false \
    vendor.audio.offload.pstimeout.secs=3 \
    vendor.audio.offload.track.enable=false \
    vendor.audio.parser.ip.buffer.size=262144 \
    vendor.audio.safx.pbe.enabled=true \
    vendor.audio.tunnel.encode=false \
    vendor.audio.use.sw.alac.decoder=true \
    vendor.audio.use.sw.ape.decoder=true \
    vendor.voice.path.for.pcm.voip=true


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
    persist.vendor.cne.feature=0

# DPM
PRODUCT_PROPERTY_OVERRIDES += \
    persist.vendor.dpm.feature=0

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
    ro.qualcomm.cabl=2 \
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
debug.egl.hw=1 \
debug.gralloc.gfx_ubwc_disable=0 \
debug.sf.enable_hwc_vds=1 \
debug.gralloc.enable_fb_ubwc=1 \
debug.sf.hw=1 \
dev.pm.dyn_samplingrate=1 \
persist.demo.hdmirotationlock=false \
persist.hwc.enable_vds=1 \
ro.persist.qcapb=1 \
sdm.debug.disable_rotator_split=1 \
sdm.debug.disable_skip_validate=1 \
sdm.perf_hint_window=50

# Media
PRODUCT_PROPERTY_OVERRIDES += \
    vendor.vidc.enc.disable.pq=true \
    vidc.enc.dcvs.extra-buff-count=2 \
    vendor.video.disable.ubwc=1

# OpenGLES
PRODUCT_PROPERTY_OVERRIDES += \
    ro.opengles.version=196610

# NFC
PRODUCT_PROPERTY_OVERRIDES += \
    ro.nfc.port=I2C

# Perf
PRODUCT_PROPERTY_OVERRIDES += \
    ro.vendor.extension_library=libqti-perfd-client.so \
    ro.vendor.qti.sys.fw.bg_apps_limit=60

# Radio
PRODUCT_PROPERTY_OVERRIDES += \
	persist.vendor.data.mode=concurrent \
	persist.data.netmgrd.qos.enable=true \
	persist.timed.enable=true \
	persist.radio.VT_CAM_INTERFACE=1 \
    persist.radio.VT_ENABLE=1 \
    persist.radio.VT_HYBRID_ENABLE=1 \
	persist.vendor.radio.apm_sim_not_pwdn=1 \
	persist.vendor.radio.custom_ecc=1 \
	persist.vendor.radio.rat_on=combine \
	persist.vendor.radio.sib16_support=1 \
	rild.libpath=/system/vendor/lib64/libril-qc-qmi-1.so \
	vendor.rild.libpath=/system/vendor/lib64/libril-qc-qmi-1.so \
	ril.subscription.types=NV,RUIM \
	ro.telephony.default_network=9 \
	ro.vendor.use_data_netmgrd=true \
	ro.vendor.wl_library=libqti-wl.so \
	ro.vendor.gt_library=libqti-gt.so \
	ro.vendor.at_library=libqti-at.so \
	persist.net.doxlat=false \
    DEVICE_PROVISIONED=1 

# Sensors
PRODUCT_PROPERTY_OVERRIDES += \
    ro.qti.sensors.dev_ori=false \
    ro.qti.sensors.pmd=false \
    ro.qti.sensors.sta_detect=false \
    ro.qti.sensors.mot_detect=false \
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

PRODUCT_PROPERTY_OVERRIDES += \
    debug.sf.early_phase_offset_ns=1500000 \
    debug.sf.early_app_phase_offset_ns=1500000 \
    debug.sf.early_gl_phase_offset_ns=3000000 \
    debug.sf.early_gl_app_phase_offset_ns=15000000

# Time services
PRODUCT_PROPERTY_OVERRIDES += \
    persist.timed.enable=true \
    persist.delta_time.enable=true

# WiFi
PRODUCT_PROPERTY_OVERRIDES += \
    wifi.interface=wlan0 \
    wifi.direct.interface=p2p-dev-wlan0

#enable Apical AD
PRODUCT_PROPERTY_OVERRIDES += \
    ro.qcom.ad=1 \
    ro.qcom.ad.sensortype=3
