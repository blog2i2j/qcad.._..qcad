/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

#ifndef RGRAPHICSSCENE_H
#define RGRAPHICSSCENE_H

#include "core_global.h"

#include <QtGlobal>

#include "RExporter.h"
#include "RRefPoint.h"

class RDocumentInterface;
class REntity;
class RGraphicsSceneDrawable;
class RGraphicsView;
class RMouseEvent;
class RTabletEvent;
class RTerminateEvent;
class RWheelEvent;
class QCursor;
class QDebug;
class QKeyEvent;
class QPanGesture;
class QPinchGesture;
class QSwipeGesture;


/**
 * Abstract base class for all graphics scenes.
 * A graphics scene is an exporter that exports entities into
 * something that can be shown in a view (painter paths,
 * triangles, OpenGL lists, ...).
 *
 * Graphics scenes store a map of reference points of all entities
 * that are currently selected. This information is stored at
 * the scene level and not at the document interface level because
 * a scene that shows for example a wall from the side may show
 * different reference points than a scene that shows the same
 * wall from the top.
 *
 * \ref RGraphicsView "graphics views".
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RGraphicsScene : public RExporter {
public:
    RGraphicsScene(RDocumentInterface& documentInterface);
    virtual ~RGraphicsScene();

    RDocumentInterface& getDocumentInterface();
    QList<RGraphicsView*> getGraphicsViews() const;

    virtual void clear();

    /**
     * Override for performance reasons, we don't need settings to be
     * exported for graphics scenes.
     */
    virtual bool exportDocumentSettings() { return true; }

    virtual void regenerate(bool undone = false, bool invisible = false);
    virtual void regenerate(QSet<RObject::Id>& affectedEntities, bool updateViews);
    virtual void updateSelectionStatus(QSet<RObject::Id>& affectedEntities, bool updateViews);
    virtual void regenerateViews(bool force=false);
    virtual void regenerateViews(QSet<RObject::Id>& affectedEntities);
    virtual void repaintViews();
    virtual void setCursor(const QCursor& cursor);

    void handleTerminateEvent(RTerminateEvent& event);

    void handleKeyPressEvent(QKeyEvent& event);
    void handleKeyReleaseEvent(QKeyEvent& event);
    void handleMouseMoveEvent(RMouseEvent& event);
    void handleMousePressEvent(RMouseEvent& event);
    void handleMouseReleaseEvent(RMouseEvent& event);
    void handleMouseDoubleClickEvent(RMouseEvent& event);
    void handleWheelEvent(RWheelEvent& event);
    void handleTabletEvent(RTabletEvent& event);
    void handleSwipeGestureEvent(QSwipeGesture& gesture);
    void handlePanGestureEvent(QPanGesture& gesture);
    void handlePinchGestureEvent(QPinchGesture& gesture);

    virtual void registerView(RGraphicsView* view, bool regen=true);
    virtual void unregisterView(RGraphicsView* view);

    virtual void beginPreview();
    virtual void endPreview();
    virtual void clearPreview();
    virtual bool isPreviewEmpty();

    virtual void addToPreview(RObject::Id entityId, QList<RGraphicsSceneDrawable>& drawables) {
        Q_UNUSED(entityId)
        Q_UNUSED(drawables)
    }
    virtual void addToPreview(RObject::Id entityId, RGraphicsSceneDrawable& drawable) {
        Q_UNUSED(entityId)
        // MSVC:
        //Q_UNUSED(drawable)
    }
    virtual void addPathToPreview(RObject::Id entityId, RPainterPath& pp) {
        Q_UNUSED(entityId)
        Q_UNUSED(pp)
    }

    void beginNoColorMode() {
        colorMode = false;
    }
    void endNoColorMode() {
        colorMode = true;
    }
    bool getNoColorMode() const {
        return !colorMode;
    }

    RRefPoint getHighlightedReferencePoint();

    /**
     * Highlights the given entity. This is typically used to highlight entities
     * when the mouse hovers over them.
     */
    virtual void highlightEntity(REntity& entity) = 0;

    virtual void highlightReferencePoint(const RRefPoint& position);

    virtual void selectReferencePoints(const RBox& box, bool add);

    virtual void exportCurrentEntity(bool preview = false, bool forceSelected = false);
    virtual void unexportEntity(RObject::Id entityId);

    int countReferencePoints() const;

    /**
     * \nonscriptable
     */
    QMap<RObject::Id, QList<RRefPoint> >& getReferencePoints() {
        return referencePoints;
    }

    bool hasSelectedReferencePoints() const;

//    virtual bool isVisualExporter() const {
//        return true;
//    }

    virtual void dump() {
        qDebug() << *this;
    }

    /**
     * \nonscriptable
     */
    friend QDebug operator<<(QDebug dbg, RGraphicsScene& gs);

protected:
    virtual void exportReferencePoints();

protected:
    RDocumentInterface& documentInterface;
    QList<RGraphicsView*> views;
    bool exportToPreview;
    // enable / disable color mode:
    bool colorMode;
    bool previewIsEmpty;
    RRefPoint highlightedReferencePoint;

    /**
     * Internal map of reference points for every selected entity in the scene.
     * Used for drawing reference points.
     */
    QMap<RObject::Id, QList<RRefPoint> > referencePoints;

private:
    bool deleting;
};

Q_DECLARE_METATYPE(QList<RGraphicsScene*>)
Q_DECLARE_METATYPE(RGraphicsScene*)

#endif
