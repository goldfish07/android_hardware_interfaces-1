/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "android.hardware.vibrator@1.0-service"
#include <utils/Log.h>

#include <iostream>
#include <unistd.h>

#include <android/hardware/vibrator/1.0/IVibrator.h>

#include <hidl/IServiceManager.h>
#include <hwbinder/IPCThreadState.h>
#include <hwbinder/ProcessState.h>
#include <utils/Errors.h>
#include <utils/StrongPointer.h>

using android::sp;

// libhwbinder:
using android::hardware::IPCThreadState;
using android::hardware::ProcessState;

// Generated HIDL files
using android::hardware::vibrator::V1_0::IVibrator;

int main() {
    ALOGI("Service is starting.");
    const char instance[] = "vibrator";
    ALOGI("Retrieving default implementation of instance %s.",
          instance);
    android::sp<IVibrator> service = IVibrator::getService(instance, true);
    if (service.get() == nullptr) {
        ALOGE("IVibrator::getService returned NULL, exiting");
        return -1;
    }
    ALOGI("Default implementation using %s is %s",
          instance, (service->isRemote() ? "REMOTE" : "LOCAL"));
    LOG_FATAL_IF(service->isRemote(), "Implementation is REMOTE!");
    ALOGI("Registering instance %s.", instance);
    service->registerAsService(instance);
    ALOGI("Ready.");

    ProcessState::self()->setThreadPoolMaxThreadCount(0);
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
}
