#include "custom-plot-item.h"

#include <QAbstractItemModel>
#include <QPainter>
#include <QPixmap>
#include <QQuickWindow>

mss::gui::CustomPlotItem::CustomPlotItem(QQuickPaintedItem* parent):
  QQuickPaintedItem(parent),
  plot_(std::make_unique< QCustomPlot >()),
  background_color_(Qt::white),
  axis_color_(Qt::black),
  grid_color_(QColor(220, 220, 220))
{
  setAntialiasing(true);
  setFlag(QQuickItem::ItemHasContents, true);

  plot_->setMinimumSize(10, 10);
  plot_->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

  plot_->axisRect()->setupFullAxesBox(true);

  applyStyle();
  applyTitle();
}

void mss::gui::CustomPlotItem::paint(QPainter* painter)
{
  if (!plot_)
  {
    return;
  }

  const int w = static_cast< int >(width());
  const int h = static_cast< int >(height());
  if (w <= 0 || h <= 0)
  {
    return;
  }

  const qreal dpr = window() ? window()->devicePixelRatio() : 1.0;
  QPixmap pixmap = plot_->toPixmap(w, h, dpr);

  if (dpr > 1.0 && qFuzzyCompare(pixmap.devicePixelRatio(), 1.0))
  {
    pixmap.setDevicePixelRatio(dpr);
  }

  painter->drawPixmap(0, 0, pixmap);
}

QString mss::gui::CustomPlotItem::getTitle() const
{
  return title_;
}

QString mss::gui::CustomPlotItem::getXLabel() const
{
  return x_label_;
}

QString mss::gui::CustomPlotItem::getYLabel() const
{
  return y_label_;
}

QColor mss::gui::CustomPlotItem::getBackgroundColor() const
{
  return background_color_;
}

QColor mss::gui::CustomPlotItem::getAxisColor() const
{
  return axis_color_;
}

QColor mss::gui::CustomPlotItem::getGridColor() const
{
  return grid_color_;
}

void mss::gui::CustomPlotItem::setTitle(const QString &val)
{
  if (title_ == val)
  {
    return;
  }
  title_ = val;
  applyTitle();
  emit titleChanged();
  update();
}

void mss::gui::CustomPlotItem::setXLabel(const QString &val)
{
  if (x_label_ == val)
  {
    return;
  }
  x_label_ = val;
  plot_->xAxis->setLabel(val);
  emit xLabelChanged();
  update();
}

void mss::gui::CustomPlotItem::setYLabel(const QString &val)
{
  if (y_label_ == val)
  {
    return;
  }
  y_label_ = val;
  plot_->yAxis->setLabel(val);
  emit yLabelChanged();
  update();
}

void mss::gui::CustomPlotItem::setBackgroundColor(const QColor &val)
{
  if (background_color_ == val)
  {
    return;
  }
  background_color_ = val;
  applyStyle();
  emit backgroundColorChanged();
  update();
}

void mss::gui::CustomPlotItem::setAxisColor(const QColor &val)
{
  if (axis_color_ == val)
  {
    return;
  }
  axis_color_ = val;
  applyStyle();
  emit axisColorChanged();
  update();
}

void mss::gui::CustomPlotItem::setGridColor(const QColor &val)
{
  if (background_color_ == val)
  {
    return;
  }
  background_color_ = val;
  applyStyle();
  emit gridColorChanged();
  update();
}

int mss::gui::CustomPlotItem::addSeries(const QString& name, const QColor& color)
{
  QCPGraph* g = plot_->addGraph();
  g->setName(name);
  g->setPen(QPen(color, 2));
  g->setLineStyle(QCPGraph::lsLine);
  g->setScatterStyle(QCPScatterStyle::ssNone);
  plot_->legend->setVisible(false);
  plot_->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignRight);

  update();
  return plot_->graphCount() - 1;
}

void mss::gui::CustomPlotItem::clearSeries()
{
  plot_->clearGraphs();
  plot_->legend->setVisible(false);
  update();
}

void mss::gui::CustomPlotItem::clear()
{
  clearSeries();
  replot();
}

void mss::gui::CustomPlotItem::setData(int series_index, const QVariantList& xs, const QVariantList& ys)
{
  if (series_index < 0 || series_index >= plot_->graphCount())
  {
    return;
  }
  if (xs.size() != ys.size())
  {
    return;
  }

  QVector< double > xv(xs.size()), yv(ys.size());
  for (int i = 0; i < xs.size(); ++i)
  {
    xv[i] = xs[i].toDouble();
    yv[i] = ys[i].toDouble();
  }
  plot_->graph(series_index)->setData(xv, yv);
  update();
}

void mss::gui::CustomPlotItem::setDataFromModel(int series_index, QAbstractItemModel* model,
  int x_column, int y_column)
{
  if (!model)
  {
    return;
  }
  if (series_index < 0 || series_index >= plot_->graphCount())
  {
    return;
  }

  const int rows = model->rowCount();
  QVector<double> xv(rows), yv(rows);
  for (int i = 0; i < rows; ++i) {
    xv[i] = model->index(i, x_column).data().toDouble();
    yv[i] = model->index(i, y_column).data().toDouble();
  }
  plot_->graph(series_index)->setData(xv, yv);
  update();
}

void::mss::gui::CustomPlotItem::addPoint(int series_index, double x, double y)
{
  if (series_index < 0 || series_index >= plot_->graphCount())
  {
    return;
  }
  plot_->graph(series_index)->addData(x, y);
}

void mss::gui::CustomPlotItem::replot()
{
  update();
}

void mss::gui::CustomPlotItem::rescaleAxes()
{
  plot_->rescaleAxes();
}

void mss::gui::CustomPlotItem::applyStyle()
{
  if (!plot_)
  {
    return;
  }

  plot_->setBackground(QBrush(background_color_));
  plot_->axisRect()->setBackground(QBrush(Qt::white));

  const QList< QCPAxis* > axes = {
    plot_->xAxis, plot_->yAxis,
    plot_->xAxis2, plot_->yAxis2
  };

  for (QCPAxis *a: axes)
  {
    a->setBasePen(QPen(axis_color_));
    a->setTickPen(QPen(axis_color_));
    a->setSubTickPen(QPen(axis_color_));
    a->setTickLabelColor(axis_color_);
    a->setLabelColor(axis_color_);
    a->grid()->setPen(QPen(grid_color_, 1, Qt::DotLine));
    a->grid()->setSubGridPen(QPen(grid_color_.lighter(130), 1, Qt::DotLine));
    a->grid()->setZeroLinePen(Qt::NoPen);
  }
}

void mss::gui::CustomPlotItem::applyTitle()
{
  if (!plot_)
  {
    return;
  }

  if (plot_->plotLayout()->rowCount() > 0)
  {
    auto *el = plot_->plotLayout()->element(0, 0);
    if (auto *te = qobject_cast< QCPTextElement* >(el))
    {
      plot_->plotLayout()->remove(te);
      plot_->plotLayout()->simplify();
      delete te;
    }
  }

  if (!title_.isEmpty())
  {
    plot_->plotLayout()->insertRow(0);
    auto *te = new QCPTextElement(plot_.get(), title_, QFont(QString(), 12, QFont::Bold));
    plot_->plotLayout()->addElement(0, 0, te);
  }
}
