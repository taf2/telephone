//
//  AppController.h
//  Telephone
//
//  Copyright (c) 2008-2009 Alexei Kuznetsov. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//  3. The name of the author may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY ALEXEI KUZNETSOV "AS IS" AND ANY EXPRESS
//  OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
//  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
//  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#import <Cocoa/Cocoa.h>
#import <Growl/Growl.h>

#import "AKTelephone.h"


@class AKTelephone, AKAccountController, AKPreferenceController, AKCallController;

@interface AppController : NSObject <AKTelephoneDelegate, GrowlApplicationBridgeDelegate> {
@private
	AKTelephone *telephone;
	NSMutableArray *accountControllers;
	AKPreferenceController *preferenceController;
	NSArray *audioDevices;
	NSInteger soundInputDeviceIndex;
	NSInteger soundOutputDeviceIndex;
	NSInteger ringtoneOutputDeviceIndex;
	NSSound *ringtone;
	NSTimer *ringtoneTimer;
	
	IBOutlet NSMenuItem *preferencesMenuItem;
}

@property(readonly, retain) AKTelephone *telephone;
@property(readonly, retain) NSMutableArray *accountControllers;
@property(readwrite, retain) AKPreferenceController *preferenceController;
@property(readwrite, retain) NSArray *audioDevices;
@property(readwrite, assign) NSInteger soundInputDeviceIndex;
@property(readwrite, assign) NSInteger soundOutputDeviceIndex;
@property(readwrite, assign) NSInteger ringtoneOutputDeviceIndex;
@property(readwrite, retain) NSSound *ringtone;
@property(readwrite, retain) NSTimer *ringtoneTimer;
@property(nonatomic, readonly, assign) BOOL hasIncomingCallControllers;
@property(nonatomic, readonly, retain) NSArray *currentNameservers;

// Hang up all calls, disconnect all accounts, destroy SIP user agent.
- (void)stopTelephone;

// Update list of available audio devices.
- (void)updateAudioDevices;

// Choose appropriate audio devices for sound IO.
- (void)selectSoundIO;

- (IBAction)showPreferencePanel:(id)sender;
- (IBAction)addAccountOnFirstLaunch:(id)sender;

- (void)startRingtoneTimer;
- (void)stopRingtoneTimer;
- (void)ringtoneTimerTick:(NSTimer *)theTimer;

// Search all account controllers for the call controller with given identifier (uuid).
- (AKCallController *)callControllerByIdentifier:(NSString *)identifier;

- (IBAction)openFAQURL:(id)sender;

- (NSString *)localizedStringForSIPResponseCode:(NSInteger)responseCode;

@end


// Audio device dictionary keys.
extern NSString * const AKAudioDeviceIdentifier;
extern NSString * const AKAudioDeviceUID;
extern NSString * const AKAudioDeviceName;
extern NSString * const AKAudioDeviceInputsCount;
extern NSString * const AKAudioDeviceOutputsCount;

// Growl notification names.
extern NSString * const AKGrowlNotificationIncomingCall;
extern NSString * const AKGrowlNotificationCallEnded;
