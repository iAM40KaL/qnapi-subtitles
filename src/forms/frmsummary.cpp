/*****************************************************************************
** QNapi
** Copyright (C) 2008-2015 Piotr Krzemiński <pio.krzeminski@gmail.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
*****************************************************************************/

#include "frmsummary.h"

frmSummary::frmSummary(QWidget * parent, Qt::WindowFlags f) : QDialog(parent, f)
{
    ui.setupUi(this);

    setAttribute(Qt::WA_QuitOnClose, false);

    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());
}

void frmSummary::setSummaryList(const QList<QPair<QString,QString>> & listSuccess, const QStringList & listFailures)
{
    ui.lwSummary->clear();

    ui.lbSuccess->setVisible(!listSuccess.isEmpty());
    ui.lbFail->setVisible(!listFailures.isEmpty());

    QIcon succIcon(":/ui/accept.png"), failIcon(":/ui/exclamation.png");

QPair<QString, QString> successItem;

    foreach(successItem, listSuccess)
    {
        QListWidgetItem* wi = new QListWidgetItem(succIcon,"[" + successItem.second.toUpper() + "] " + QFileInfo(successItem.first).fileName());

        ui.lwSummary->addItem(wi);
    }

    foreach(QString failureItem, listFailures)
    {
        ui.lwSummary->addItem(new QListWidgetItem(failIcon, QFileInfo(failureItem).fileName()));
    }

    ui.lbSuccess->setText(tr("Pobrano napisy dla %1 %2")
                          .arg(listSuccess.size())
                          .arg(tr(listSuccess.size() > 1 ? "plików" : "pliku")));

    ui.lbFail->setText(tr("Nie pobrano napisów dla %1 %2")
                       .arg(listFailures.size())
                       .arg(tr(listFailures.size() > 1 ? "plików" : "pliku")));
}
