#include "utils/Helpers.h"

#include <QPlainTextEdit>
#include <QTextEdit>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QTreeWidget>
#include <QString>
#include <QAbstractItemView>
#include <QAbstractButton>
#include <QDockWidget>
#include <QtGui/QtGui>


static QAbstractItemView::ScrollMode scrollMode()
{
    const bool use_scrollperpixel = true;
    return use_scrollperpixel ? QAbstractItemView::ScrollPerPixel : QAbstractItemView::ScrollPerItem;
}


namespace qhelpers
{
    void adjustColumns(QTreeWidget *tw, int columnCount, int padding)
    {
        const int count = columnCount == 0 ? tw->columnCount() : columnCount;
        for (int i = 0; i != count; ++i)
        {
            tw->resizeColumnToContents(i);
            if (padding > 0)
            {
                int width = tw->columnWidth(i);
                tw->setColumnWidth(i, width + padding);
            }
        }
    }

    QTreeWidgetItem *appendRow(QTreeWidget *tw, const QString &str, const QString &str2,
                               const QString &str3, const QString &str4, const QString &str5)
    {
        QTreeWidgetItem *tempItem = new QTreeWidgetItem();
        // Fill dummy hidden column
        tempItem->setText(0, "0");
        tempItem->setText(1, str);
        if (!str2.isNull())
            tempItem->setText(2, str2);
        if (!str3.isNull())
            tempItem->setText(3, str3);
        if (!str4.isNull())
            tempItem->setText(4, str4);
        if (!str5.isNull())
            tempItem->setText(5, str5);

        tw->insertTopLevelItem(0, tempItem);

        return tempItem;
    }

    void setVerticalScrollMode(QAbstractItemView *tw)
    {
        tw->setVerticalScrollMode(scrollMode());
    }

    void setCheckedWithoutSignals(QAbstractButton *button, bool checked)
    {
        bool blocked = button->signalsBlocked();
        button->blockSignals(true);
        button->setChecked(checked);
        button->blockSignals(blocked);
    }


    SizePolicyMinMax forceWidth(QWidget *widget, int width)
    {
        SizePolicyMinMax r;
        r.sizePolicy = widget->sizePolicy();
        r.min = widget->minimumWidth();
        r.max = widget->maximumWidth();

        QSizePolicy sizePolicy = r.sizePolicy;
        sizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumWidth(width);
        widget->setMaximumWidth(width);

        return r;
    }


    SizePolicyMinMax forceHeight(QWidget *widget, int height)
    {
        SizePolicyMinMax r;
        r.sizePolicy = widget->sizePolicy();
        r.min = widget->minimumHeight();
        r.max = widget->maximumHeight();

        QSizePolicy sizePolicy = r.sizePolicy;
        sizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumHeight(height);
        widget->setMaximumHeight(height);

        return r;
    }

    void SizePolicyMinMax::restoreWidth(QWidget *widget)
    {
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumWidth(min);
        widget->setMaximumWidth(max);
    }

    void SizePolicyMinMax::restoreHeight(QWidget *widget)
    {
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumHeight(min);
        widget->setMaximumHeight(max);
    }


    int getMaxFullyDisplayedLines(QPlainTextEdit *plainTextEdit)
    {
        QFontMetrics fontMetrics(plainTextEdit->document()->defaultFont());
        return (plainTextEdit->height()
                - (plainTextEdit->contentsMargins().top()
                   + plainTextEdit->contentsMargins().bottom()
                   + (int)(plainTextEdit->document()->documentMargin() * 2)))
               / fontMetrics.lineSpacing();
    }

} // end namespace
