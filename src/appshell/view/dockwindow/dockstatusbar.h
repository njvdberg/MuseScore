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
#ifndef MU_DOCK_DOCKSTATUSBAR_H
#define MU_DOCK_DOCKSTATUSBAR_H

#include "dockview.h"

class QWidget;

namespace mu::dock {
class DockStatusBar : public DockView
{
    Q_OBJECT

public:
    explicit DockStatusBar(QQuickItem* parent = nullptr);
    ~DockStatusBar();

    struct Widget {
        QWidget* widget = nullptr;
    };

    Widget widget() const;

    bool visible() const override;

public slots:
    void setVisible(bool visible) override;

private:
    void onComponentCompleted() override;

    Widget m_widget;
    bool m_visible = false;
};
}

#endif // MU_DOCK_DOCKSTATUSBAR_H
