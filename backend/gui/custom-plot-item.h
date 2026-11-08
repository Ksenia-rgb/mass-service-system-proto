#ifndef CUSTOM_PLOT_ITEM_H
#define CUSTOM_PLOT_ITEM_H

#pragma once

#include <QQuickPaintedItem>
#include <QColor>
#include <QVariantList>

#include "libs/qcustomplot/qcustomplot.h"

namespace mss
{
  namespace gui
  {
    class CustomPlotItem: public QQuickPaintedItem
    {
      Q_OBJECT
      Q_PROPERTY(QString title READ getTitle WRITE setTitle NOTIFY titleChanged)
      Q_PROPERTY(QString xLabel READ getXLabel WRITE setXLabel NOTIFY xLabelChanged)
      Q_PROPERTY(QString yLabel READ getYLabel WRITE setYLabel NOTIFY yLabelChanged)
      Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
      Q_PROPERTY(QColor axisColor READ getAxisColor WRITE setAxisColor NOTIFY axisColorChanged)
      Q_PROPERTY(QColor gridColor READ getGridColor WRITE setGridColor NOTIFY gridColorChanged)
    public:
      CustomPlotItem(QQuickPaintedItem* parent = nullptr);
      ~CustomPlotItem() override = default;

      void paint(QPainter* painter) override;

      QString getTitle() const;
      QString getXLabel() const;
      QString getYLabel() const;
      QColor getBackgroundColor() const;
      QColor getAxisColor() const;
      QColor getGridColor() const;

      void setTitle(const QString& val);
      void setXLabel(const QString& val);
      void setYLabel(const QString& val);
      void setBackgroundColor(const QColor& val);
      void setAxisColor(const QColor& val);
      void setGridColor(const QColor& val);

      Q_INVOKABLE int addSeries(const QString& name, const QColor& color);
      Q_INVOKABLE void clearSeries();
      Q_INVOKABLE void clear();
      Q_INVOKABLE void setData(int series_index, const QVariantList& xs, const QVariantList& ys);
      Q_INVOKABLE void setDataFromModel(int series_index, QAbstractItemModel* model,
        int x_column, int y_column);
      Q_INVOKABLE void addPoint(int series_index, double x, double y);
      Q_INVOKABLE void replot();
      Q_INVOKABLE void rescaleAxes();
    signals:
      void titleChanged();
      void xLabelChanged();
      void yLabelChanged();
      void backgroundColorChanged();
      void axisColorChanged();
      void gridColorChanged();
    private:
      void applyStyle();
      void applyTitle();

      std::unique_ptr< QCustomPlot > plot_;

      QString title_;
      QString x_label_;
      QString y_label_;
      QColor background_color_;
      QColor axis_color_;
      QColor grid_color_;
    };
  }
}

#endif
