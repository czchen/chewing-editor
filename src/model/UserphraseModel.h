/*
 * chewing-editor: Chewing userphrase editor
 * Copyright (C) 2014 ChangZhuo Chen

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include <memory>

#include <QAbstractListModel>
#include <QString>

#include <chewing.h>

#include "Userphrase.h"
#include "UserphraseExporter.h"
#include "UserphraseImporter.h"
#include "UserphraseSet.h"

class UserphraseModel final: public QAbstractListModel {
    Q_OBJECT

public:
    UserphraseModel(QObject * parent = 0, const char *path = nullptr);
    UserphraseModel(const UserphraseModel& x) = delete;
    UserphraseModel& operator=(const UserphraseModel& x) = delete;
    virtual ~UserphraseModel() = default;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void remove(QModelIndexList &&indexList);
    bool add(const QString &phrase, const QString &bopomofo);

    void importUserphrase(UserphraseImporter& importer);
    void exportUserphrase(UserphraseExporter& exporter);

signals:
    void refreshCompleted(size_t count);
    void importCompleted(
        bool result,
        const QString& file,
        size_t imported,
        size_t total);
    void addNewPhraseCompleted(const Userphrase& userphrase);

public slots:
    void refresh();

private:

    std::unique_ptr<ChewingContext, void (*)(ChewingContext*)> ctx_;
    UserphraseSet userphrase_;
};
