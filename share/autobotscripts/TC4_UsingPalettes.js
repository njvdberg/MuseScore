/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

var NewScore = require("steps/NewScore.js")
var NoteInput = require("steps/NoteInput.js")
var Palette = require("steps/Palette.js")

var testCase = {
    name: "TC4: Using palettes",
    description: "Let's check the functionality of the palettes",
    steps: [
        {name: "Close score (if opened) and go to home to start", func: function() {
            api.dispatcher.dispatch("file-close")
            api.navigation.triggerControl("TopTool", "MainToolBar", "Home")
        }},
        {name: "Open New Score Dialog", func: function() {
            NewScore.openNewScoreDialog()
        }},
        {name: "Create score", func: function() {
            NewScore.сhooseInstrument("Woodwinds", "Flute")
            NewScore.done()
        }},
        {name: "Change Clefs", skip: false, func: function() {
            //! NOTE First, we need to select the current Clef
            api.navigation.goToControl("NotationView", "ScoreView", "Score") // The first rest is selected by default.
            api.shortcuts.activate("Alt+Left") // select Time sig
            api.shortcuts.activate("Alt+Left") // select Clef
            seeChanges()

            //! NOTE Return to Palettes and expand Clefs
            Palette.togglePalette("Clefs")
            seeChanges()
            applyCellByCell(24, 0) //24
        }},
        {name: "Change Key signatures", skip: false, func: function() {
            //! NOTE To change Key sig, we need to select the first Chord on score
            api.navigation.goToControl("NotationView", "ScoreView", "Score")
            api.shortcuts.activate("Alt+Right") // select Time sig
            api.shortcuts.activate("Alt+Right") // select Rest

            //! NOTE Return to Palettes and expand Key signatures
            Palette.togglePalette("Key signatures")
            seeChanges()
            applyCellByCell(16, 1) //16 (14 - no key sig)
        }},
        {name: "Change Time signatures", skip: true, func: function() {
            Palette.togglePalette("Time signatures")
            seeChanges()
            applyCellByCell(17, 2)
        }},
        {name: "Add Accidentals", skip: true, func: function() {
            Palette.togglePalette("Accidentals") // open
            putNoteAndApplyCell(11)
            Palette.togglePalette("Accidentals") // close
        }},
        {name: "Add Articulations", func: function() {
            Palette.togglePalette("Articulations") // open
            putNoteAndApplyCell(34)
            Palette.togglePalette("Articulations") // close
        }},
        {name: "Change Noteheads", func: function() {
            Palette.togglePalette("Noteheads") // open
            putNoteAndApplyCell(24)
            Palette.togglePalette("Noteheads") // close
        }},
        {name: "Save", func: function() {
            api.autobot.saveProject("TC3 Using note input toolbar.mscz")
        }},
        {name: "Close", func: function() {
            api.dispatcher.dispatch("file-close")
        }},
        {name: "Home", func: function() {
            api.navigation.triggerControl("TopTool", "MainToolBar", "Home")
        }},
        {name: "Open last", func: function() {
            api.navigation.goToControl("RecentScores", "RecentScores", "New score")
            api.navigation.right()
            api.navigation.trigger()
        }}
    ]
};

function main()
{
    api.autobot.setInterval(500)
    api.autobot.runTestCase(testCase)
}

function seeChanges()
{
    api.autobot.seeChanges()
}

function applyCellByCell(count, keep_index)
{
    // apply
    for (var i = 0; i < count; i++) {
        api.navigation.down()
        api.navigation.trigger()
        seeChanges()
    }

    // back

    for (var r = (count - 1); r >= 0; r--) {
        api.navigation.up()
        api.autobot.seeChanges(100)

        // keep
        if ((keep_index + 1) === r) {
            api.navigation.trigger()
        }
    }

    // collapse
    api.navigation.trigger()
}

function putNoteAndApplyCell(count)
{
    for (var i = 0; i < count; i++) {
        api.shortcuts.activate("C")
        api.navigation.down()
        api.navigation.trigger()
        seeChanges()
    }
}


