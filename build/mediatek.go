package mediatekBluetooth

import (
	"android/soong/android"
	"android/soong/cc"
)

func MtkGlobalDefaults(ctx android.BaseContext) ([]string, []string) {
	var cflags []string
	var includeDirs []string
	/************************************************
	* ** General Config
	* ***********************************************/
	vars := ctx.Config().VendorConfig("mtkPlugin")
	cflags = append(cflags, "-DHAS_MDROID_BUILDCFG")
	includeDirs = append(includeDirs, "system/bt/mediatek/include")

	// MTK interop extension
	if vars.Bool("MSSI_MTK_BT_INTEROP_EXTENSION") {
		cflags = append(cflags, "-DMTK_INTEROP_EXTENSION=TRUE")
	}

	// Custom AVRCP APP Settings feature
	cflags = append(cflags, "-DMTK_AVRCP_APP_SETTINGS=TRUE")

	// Enable BLE VND Feature for MTK BT
	cflags = append(cflags, "-DBLE_VND_INCLUDED=TRUE")

	// MTK adjust a2dp packet length of SBC as 2-DH5/3-DH5 for firmware
	cflags = append(cflags, "-DMTK_VND_A2DP_PKT_LEN=TRUE")

	// MTK modifies the AOSP for bug fixing
	cflags = append(cflags, "-DMTK_BT_PROPRIETARY_HANDLING=TRUE")

	// MTK support customized snoop log
	if vars.Bool("MSSI_MTK_BT_HOST_SNOOP_LOG_SUPPORT") {
		cflags = append(cflags, "-DMTK_STACK_CONFIG_LOG=TRUE")
	}

	// MTK a2dp hal layer PCM dump
	cflags = append(cflags, "-DMTK_A2DP_PCM_DUMP=TRUE")

	return cflags, includeDirs
}

func init() {
	android.RegisterModuleType("mtk_hcidebug_defaults", mtkHciDebugDefaultsFactory)
}

func mtkHciDebugDefaultsFactory() android.Module {
	module := cc.DefaultsFactory()
	android.AddLoadHook(module, mtkHciDebugDefaults)
	return module
}

func mtkHciDebugDefaults(ctx android.LoadHookContext) {
	type props struct {
		Cflags []string
		Include_dirs   []string
		Shared_libs []string
	}
	p := &props{}
	vars := ctx.Config().VendorConfig("mtkPlugin")
	if vars.String("TARGET_BUILD_VARIANT") != "user" {
		// MTK hci debug
		p.Cflags = append(p.Cflags, "-DMTK_HCI_DEBUG=1")
		if vars.Bool("HAVE_AEE_FEATURE") {
			p.Cflags = append(p.Cflags, "-DHAVE_AEE_FEATURE")
			p.Include_dirs = append(p.Include_dirs, "vendor/mediatek/proprietary/external/aee/binary/inc")
			p.Shared_libs = append(p.Shared_libs, "libaed")
		}
		p.Shared_libs = append(p.Shared_libs, "libutilscallstack")
	}
	ctx.AppendProperties(p)
}
