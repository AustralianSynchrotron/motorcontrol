#ifndef QCAMOTORGUILOCAL_H
#define QCAMOTORGUILOCAL_H

#include "qcamotorgui.h"

/// The table model containing the descriptions of all motors
/// PVs known to the program. Used for the "Choose PV" dialog (Ui::PVtable)
///
class KnownPVTable : public QAbstractTableModel {

  Q_OBJECT;

private:

  QList <QEpicsPv*> knownPVs;   ///< List of the motors' description fields.

  /// SAearches for the pv in the ::knownPVs list.
  ///
  /// @param pv PV to search for.
  ///
  /// @return the index of the pv in the ::knownPVs list if found or invalid index if
  /// the pv was not found in the list.
  ///
  QModelIndex indexOf(QEpicsPv* pv) const;

public:

  /// Constructor
  ///
  /// @param list List of known motor PVs.
  /// @param parent Parent of the object.
  ///
  /// @return
  ///
  KnownPVTable(const QStringList &list, QObject *parent=0);

  /// Implements QAbstractTableModel::rowCount()
  /// @param parent unused.
  /// @return number of rows in the table: size of the ::knownPVs.
  int rowCount(const QModelIndex &parent) const;

  /// Implements QAbstractTableModel::columnCount()
  /// @param parent unused.
  /// @return number of columns in the table. Always 2: motor's PV and the description.
  int columnCount(const QModelIndex &parent) const;

  /// Data stored in the table. Implements the QAbstractTableModel::data().
  ///
  /// @param index Index of the cell.
  /// @param role Role of the data.
  ///
  /// @return Data stored in the cell under the role.
  ///
  QVariant data(const QModelIndex &index, int role) const;

  /// Data in the table's (horizontal) header. Implements QAbstractTableModel::headerData().
  ///
  /// @param section table's column.
  /// @param orientation Header's orientation (only Qt::Horizontal will get some data).
  /// @param role Role of the data.
  ///
  /// @return Data for the header.
  ///
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private slots:

  void updateData();            ///< Slot used to catch the data change.

};


/// \brief Event filter to modify the key press behaviour in the "Choose PV" dialog.
///
/// The dialog contains only two widgets: the search field and the table view. The main idea
/// is to redirect any text-editing key stroke into the search field (they have ho effect
/// in the table view) and up/down navigation to the table view (no effect in the search),
/// leaving only the Enter, Home, End key events where it happened.
///
class KeyPressEater : public QObject {
  Q_OBJECT;
public:
  /// Contructor
  /// @param parent object's parent.
  KeyPressEater(QObject * parent) : QObject(parent) {}
protected:
  /// The event filter. Re-implementation of the Object::eventFilter()
  /// @param obj the object.
  /// @param event key press event.
  /// @return same as in Object::eventFilter().
  bool eventFilter(QObject *obj, QEvent *event);
};





#endif // QCAMOTORGUILOCAL_H
