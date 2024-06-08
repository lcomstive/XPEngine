if(ANDROID)
	add_library(AndroidAppGlue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

	list(APPEND ENGINE_DEPENDENCY_LIBS AndroidAppGlue)
	list(APPEND ENGINE_DEPENDENCY_INCLUDE_DIRS ${ANDROID_NDK}/sources/android/native_app_glue)
endif()