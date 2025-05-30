// Copyright © 2023-2024 ChefKiss. Licensed under the Thou Shalt Not Profit License version 1.5.
// See LICENSE for details.

#pragma once
#include "SMCRSCard.hpp"
#include <Headers/kern_iokit.hpp>
#include <IOKit/IOService.h>
#include <VirtualSMCSDK/AppleSmcBridge.hpp>
#include <VirtualSMCSDK/kern_vsmcapi.hpp>

class EXPORT PRODUCT_NAME : public IOService {
    OSDeclareDefaultStructors(PRODUCT_NAME);

    static constexpr size_t MaxIndexCount = sizeof("0123456789ABCDEF") - 1;
    static constexpr const char *KeyIndexes = "0123456789ABCDEF";

    static constexpr SMC_KEY KeyTGxP(size_t i) { return SMC_MAKE_IDENTIFIER('T', 'G', KeyIndexes[i], 'P'); }
    static constexpr SMC_KEY KeyTGxD(size_t i) { return SMC_MAKE_IDENTIFIER('T', 'G', KeyIndexes[i], 'D'); }
    static constexpr SMC_KEY KeyTGxp(size_t i) { return SMC_MAKE_IDENTIFIER('T', 'G', KeyIndexes[i], 'p'); }
    static constexpr SMC_KEY KeyTGxd(size_t i) { return SMC_MAKE_IDENTIFIER('T', 'G', KeyIndexes[i], 'd'); }
    static constexpr SMC_KEY KeyTGDD = SMC_MAKE_IDENTIFIER('T', 'G', 'D', 'D');
    static constexpr SMC_KEY KeyPGxR(size_t i) { return SMC_MAKE_IDENTIFIER('P', 'G', KeyIndexes[i], 'R'); }
    static constexpr SMC_KEY KeyPGxC(size_t i) { return SMC_MAKE_IDENTIFIER('P', 'G', KeyIndexes[i], 'C'); }

    VirtualSMCAPI::Plugin vsmcPlugin {
        .product = xStringify(PRODUCT_NAME),
        .version = parseModuleVersion(xStringify(MODULE_VERSION)),
        .apiver = VirtualSMCAPI::Version,
    };

    OSArray *cards {nullptr};
    IONotifier *vsmcNotifier {nullptr};

    public:
    IOService *probe(IOService *provider, SInt32 *score) APPLE_KEXT_OVERRIDE;
    bool start(IOService *provider) APPLE_KEXT_OVERRIDE;
    void free() APPLE_KEXT_OVERRIDE;
    void stop(IOService *provider) APPLE_KEXT_OVERRIDE;

    virtual UInt32 getCardCount();
    virtual SMCRSCard *getCard(UInt32 index);
    virtual UInt16 getTemperature(UInt32 index);
    virtual float getPower(UInt32 index);

    static bool vsmcNotificationHandler(void *target, void *refCon, IOService *newService, IONotifier *notifier);
};
