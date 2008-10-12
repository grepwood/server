//////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
//////////////////////////////////////////////////////////////////////
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//////////////////////////////////////////////////////////////////////

#include "otpch.h"

#include "script enviroment.h"
#include "script listener.h"

using namespace Script;

Enviroment::Enviroment() {
}

Enviroment::~Enviroment() {
}

void Enviroment::cleanup() {
	object_map.clear();
	objectID_counter = 0;
	Generic.OnSay.clear();
}

void Enviroment::cleanupUnusedListeners(ListenerList& list) {
	for(ListenerList::iterator giter = list.begin(),
		gend = list.end();
		giter != gend;)
	{
		if((*giter)->isActive() == false) {
			giter = list.erase(giter);
		} else ++giter;
	}
}

void Enviroment::cleanupUnusedListeners() {
	cleanupUnusedListeners(Generic.OnSay);
}

bool Enviroment::stopListener(ListenerList& list, uint32_t id) {
	for(ListenerList::iterator giter = list.begin(),
		gend = list.end();
		giter != gend;
		++giter)
	{
		if((*giter)->getID() == id && (*giter)->isActive()) {
			(*giter)->deactive();
			return true;
		}
	}
	return false;
}

bool Enviroment::stopListener(ListenerType type, uint32_t id) {
	if(type == ONSAY_LISTENER) {
		if(stopListener(Generic.OnSay, id)) return true;
	}

	// Try creatures
	;

	return false;
}

bool Enviroment::stopListener(Listener* listener) {
	return stopListener(listener->type(), listener->getID());
}