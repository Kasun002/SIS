/****************************************************************************
*
*  Copyright (C) 2002-2008 Helta Kft. / NociSoft Software Solutions
*  All rights reserved.
*  Author: Norbert Szabo
*  E-mail: nszabo@helta.hu, info@nocisoft.com
*  Web: www.nocisoft.com
*
*  This file is part of the NCReport reporting software
*
*  Licensees holding a valid NCReport License Agreement may use this
*  file in accordance with the rights, responsibilities, and obligations
*  contained therein. Please consult your licensing agreement or contact
*  nszabo@helta.hu if any conditions of this licensing are not clear
*  to you.
*
*  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
*  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
****************************************************************************/
#ifndef NCREPORTELLIPSEITEM_H
#define NCREPORTELLIPSEITEM_H

#include "ncreportshapeitem.h"

/*!
Ellipse item data class
 */
class NCReportEllipseData : public NCReportShapeData
{
public:
    NCReportEllipseData() : rect(QRectF()) {}
    QRectF rect;
};

/*!
Ellipse item class
 */
class NCReportEllipseItem : public NCReportShapeItem
{
public:
    NCReportEllipseItem( NCReportDef* rdef, QGraphicsItem* parent =0);
    ~NCReportEllipseItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setRect(const QRectF &rect);
    bool read( NCReportXMLReader* );
    bool write( NCReportXMLWriter* );
    void setDefaultForEditor();
    void paint( NCReportOutput*, const QPointF& );

private:
    NCReportEllipseData* m_d;
};

#endif
