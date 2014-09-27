//
//  NotificationCenter.h
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 14.05.12.
//
//
// The MIT License (MIT)
//
// Copyright (c) 2012 Eduard Feicho
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//

#ifndef __NOTIFICATIONCENTER_H
#define __NOTIFICATIONCENTER_H


#include <string>
#include <vector>
using namespace std;


#define MOUSE_CLICK_NOTIFICATION              "Notification.Input.MouseClick"
#define PARTICLEGENERATOR_SPIRAL_NOTIFICATION "Notification.Particles.Spiral"
#define PARTICLEGENERATOR_SINE_NOTIFICATION   "Notification.Particles.Sine"



/**
 * class Notification acts as message class for notification events.
 * The notification is identifyable by a string called ID.
 * The notification may contain a pointer to an object that is sent along with the notification.
 * The receiver of the notification identifies the event by it's ID and casts the void* to an
 * object of his expectation.
 */
class Notification
{
public:
	Notification() : _object(NULL) {}
	Notification(string notificationID, void* reference)
	: _ID(notificationID), _object(reference) {
	}
	
	void* getObject() {
		return _object;
	}
	
	string getID() {
		return _ID;
	}
	
private:
	// notification ID for identification purposes
	string _ID;
	
	// pointer to an object of interest send to observers with the notification.
	void* _object;
};



/**
 * class NotificationObserver is an interface that observers have to implement in
 * order to be able to receive notifications.
 */
class NotificationObserver
{
public:
	virtual void notify(Notification notification) = 0;
};



/**
 * class NotificationObserverElement is an entry for observers in the list of observers.
 * It contains a pointer to the observer and the notification ID in form of a string, which
 * notification the observer is interested in.
 */
class NotificationObserverElement
{
public:
	NotificationObserverElement(string identity, NotificationObserver* ref)
	: notificationID(identity), observer(ref) {
	}
	
	// id of notification the observer is interested in
	string notificationID;
	
	// pointer to the observer that implements the NotificationObserver interface
	NotificationObserver* observer;
	
	NotificationObserverElement& operator=(NotificationObserverElement const& rhs) {
		// Only do assignment if RHS is a different object from this.
		if (this != &rhs) {
			// copy values
			this->notificationID = rhs.notificationID;
			this->observer = rhs.observer;
		}
		return *this;
	}
};



/**
 * class NotificationCenter can be used to send instant event notifications to
 * objects that implement the NotificationObserver interface.
 * Using a Singleton pattern, the class can be referenced anywhere in the code in a modular way.
 */
class NotificationCenter
{
public:
	// Singleton pattern instance
	static NotificationCenter* defaultCenter() {
		static NotificationCenter* singleton = NULL;
		if (singleton == NULL) {
			singleton = new NotificationCenter();
		}
		return singleton;
	}
	
	// Observer pattern: add an observer for given notification
	void addObserver(string ID, NotificationObserver* observer) {
		observers.push_back(NotificationObserverElement(ID, observer));
	}
	
	// Observer pattern: remove observer for given notification
	void removeObserver(string ID, NotificationObserver* observer) {
		for (vector<NotificationObserverElement>::iterator it = observers.begin();
			   it != observers.end();
			     it++) {
			if (it->notificationID == ID && it->observer == observer) {
				observers.erase(it);
				break;
			}
		}
	}
	
	/* Observer pattern: post a notification using
	 * notificationID as identificator and
	 * passing a pointer to an object of interest
	 */
	void postNotification(string notificationID, void* object) {
		for (vector<NotificationObserverElement>::iterator it = observers.begin();
			   it != observers.end();
			     it++) {
			if (it->notificationID == notificationID) {
				it->observer->notify(Notification(notificationID, object));
			}
		}
	}
	
private:
	
	NotificationCenter() {}
	vector<NotificationObserverElement> observers;
	
};

#endif
