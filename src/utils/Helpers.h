#ifndef QHELPERS_H
#define QHELPERS_H

#include <QString>
#include <QSizePolicy>

class QPlainTextEdit;
class QTextEdit;
class QString;
class QTreeWidget;
class QTreeWidgetItem;
class QAbstractItemView;
class QAbstractButton;
class QWidget;

namespace qhelpers
{
    void adjustColumns(QTreeWidget *tw, int columnCount = 0, int padding = 0);

    QTreeWidgetItem *appendRow(QTreeWidget *tw, const QString &str, const QString &str2 = QString(),
                               const QString &str3 = QString(), const QString &str4 = QString(), const QString &str5 = QString());

    void setVerticalScrollMode(QAbstractItemView *tw);

    void setCheckedWithoutSignals(QAbstractButton *button, bool checked);


    struct SizePolicyMinMax
    {
        QSizePolicy sizePolicy;
        int min;
        int max;

        void restoreWidth(QWidget *widget);
        void restoreHeight(QWidget *widget);
    };

    SizePolicyMinMax forceWidth(QWidget *widget, int width);
    SizePolicyMinMax forceHeight(QWidget *widget, int height);


    int getMaxFullyDisplayedLines(QPlainTextEdit *plainTextEdit);
}

#endif // HELPERS_H
