plugins {
    alias(libs.plugins.android.application)
}

android {
    namespace = "com.madissia.xpapp"
	compileSdk = 34

    defaultConfig {
        applicationId = "com.madissia.xpapp"
        minSdk = 24
		targetSdk = 34
    }

    externalNativeBuild {
        cmake {
            path = file("../../../CMakeLists.txt")
        }
    }
}
