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
#ifndef NCREPORTSHAPEITEM_H
#define NCREPORTSHAPEITEM_H

#include "ncreportitem.h"

#include <QPen>
#include <QBrush>
#include <QPointF>
#include <QRectF>

/*!
Shape item's data class. The class stores the properties of the item
*/
class NCReportShapeData : public NCReportItemData
{
public:
    NCReportShapeData() : lineWidthMM(0.2) {}

    qreal lineWidthMM;
    //qreal dynLineWidthMM;
    QPen pen;
	QBrush brush;
	QRectF boundingRect;

    QString dynFillColorSource;
    QString dynLineColorSource;
    QString dynLineWidthSource;
    //QColor dynFillColor;
    //QColor dynLineColor;
};

/*!
Abstract shape item class.
 */
class NCReportShapeItem : public NCReportItem
{
public:
 	NCReportShapeItem( QGraphicsItem* parent =0);
 	~NCReportShapeItem();
	//QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	
	virtual bool read( NCReportXMLReader* r);
	virtual bool write( NCReportXMLWriter* w);
	virtual void paint( NCReportOutput*, const QPointF& ) =0;
	virtual bool isObscuredBy(const QGraphicsItem *item) const;
	virtual QPainterPath opaqueArea() const;
	virtual bool isLine() const;
	static QPainterPath shapeFromPath(const QPainterPath &path, const QPen &pen);
    virtual void updateValue( NCReportOutput* output, NCReportEvaluator* evaluator);
	
	inline QPen pen() const
	{ return ((NCReportShapeData*)d)->pen; }

	inline QBrush brush() const
	{ return ((NCReportShapeData*)d)->brush; }

	virtual void setBrush( const QBrush & brush );
	virtual void setPen( const QPen & pen );

	inline qreal lineWidth() const
    { return ((NCReportShapeData*)d)->lineWidthMM; }

    void setLineWidth( qreal width )
    { ((NCReportShapeData*)d)->lineWidthMM = width; }

    void setDynamicFillColorSource( const QString& source )
    { ((NCReportShapeData*)d)->dynFillColorSource = source; }
    QString dynamicFillColorSource() const
    { return ((NCReportShapeData*)d)->dynFillColorSource; }

    void setDynamicLineColorSource( const QString& source )
    { ((NCReportShapeData*)d)->dynLineColorSource = source; }
    QString dynamicLineColorSource() const
    { return ((NCReportShapeData*)d)->dynLineColorSource; }

    void setDynamicLineWidthSource( const QString& source )
    { ((NCReportShapeData*)d)->dynLineWidthSource = source; }
    QString dynamicLineWidthSource() const
    { return ((NCReportShapeData*)d)->dynLineWidthSource; }

};



#endif
