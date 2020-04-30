//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2020 MuseScore BVBA and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================

#ifndef DYNRANGEFILTER_H
#define DYNRANGEFILTER_H

#include "score.h"
#include "dynamic.h"
#include "hairpin.h"

namespace Ms {

//---------------------------------------------------------
//   DynRangeFilter
//---------------------------------------------------------

template <class T>
class DynRangeFilter {
      Score* _score;
      int    _track;
      bool   _voiceToPart;

      // priority:
      //    0 - no dynamic/hairpin found yet.
      //    1 - system dynamic/hairpin found.
      //    2 - system dynamic/hairpin found and track is first track of part.
      //    3 - part dynamic/hairpin found.
      //    4 - part dynamic/hairpin found and track is first track of part.
      //    5 - staff dynamic/hairpin found.
      //    6 - staff dynamic/hairpin found and track is first track of staff.
      //    7 - dedicated dynamic/hairpin for track found.
      int    _priority;
      T*     _active;

   public:
      DynRangeFilter(Score* score, int track, bool voiceToPart)
            : _score(score), _track(track), _voiceToPart(voiceToPart)
            {
            _active = nullptr;
            _priority = 0;
            }

      T* addElement(T* element)
            {
            int first = _score->firstTrackOfPart(element->track());
            switch (element->dynRange()) {
                  case Dynamic::Range::VOICE:
                        if (element->track() == _track)
                              _active = element;
                        return _active;
                        break;
                  case Dynamic::Range::STAFF:
                        if (_priority > 5)
                              break;
                        if (element->staffIdx() == (_track >> 2)) {
                              if (_track == element->track()) {
                                    _active = element;
                                    _priority = 5;
                                    }
                              else {
                                    if (_voiceToPart)
                                          _active = element;
                                    _priority = 6;
                                    }
                        }
                        break;
                  case Dynamic::Range::PART:
                        if (_priority > 3)
                              break;
                        if ((first <= _track) && (_track <= _score->lastTrackOfPart(element->track()))) {
                              if (_track == element->track()) {
                                    _active = element;
                                    _priority = 4;
                                    }
                              else {
                                    if (_voiceToPart)
                                          _active = element;
                                    _priority = 3;
                                    }
                              }
                        break;
                  case Dynamic::Range::SYSTEM:
                        if (_priority > 1)
                              break;
                        if (_track == element->track()) {
                              _active = element;
                              _priority = 2;
                        }
                        else {
                              if (_voiceToPart)
                                    _active = element;
                              else if ((_track == _score->firstTrackOfPart(_track))
                                          && ((_track < first) || (_track > _score->lastTrackOfPart(element->track()))))
                                    _active = element;
                              _priority = 1;
                              }
                        break;
                  }
            return nullptr;
            }
      T* active() { return _active; }
      };

} // Ms

#endif // DYNRANGEFILTER_H
