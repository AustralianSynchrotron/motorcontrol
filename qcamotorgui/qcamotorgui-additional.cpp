#include "qcamotorgui-additional.h"
#include "ui_qcamotorgui-pv.h"
#include <QSortFilterProxyModel>
#include <QStandardPaths>
#include <QHBoxLayout>
#include <QDir>





StepValidator::StepValidator(QWidget * parent)  :
  QValidator(parent),
  last(),
  min(-2147483647),
  max(2147483647)
{}

QValidator::State StepValidator::validate ( QString & input, int &) const {
  bool okst;
  double ndouble = input.toDouble(&okst);
  return ( input == "jog" ||
           ( okst && ndouble >= min && ndouble <= max ) )
      ?  Acceptable  :  Intermediate ;
}




void QMultiComboBox::keyPressEvent( QKeyEvent * event ) {
  QComboBox::keyPressEvent(event);
  int key = event->key();
  if ( key == Qt::Key_Enter || key == Qt::Key_Return )
    emit textEdited(currentText());
  else if ( key == Qt::Key_Escape )
    emit escaped();
}

void QMultiComboBox::focusInEvent(QFocusEvent * event){
  QComboBox::focusInEvent(event);
  stepValidator->setLast(currentText());
}

void QMultiComboBox::focusOutEvent(QFocusEvent * event){
  QComboBox::focusOutEvent(event);
  emit escaped();
}


void QMultiComboBox::fixup() {
  QString fixstring = currentText();
  validator()->fixup(fixstring);
  int idx = findText(fixstring);
  if (idx >= 0)
    setCurrentIndex(idx);
}



QMultiComboBox::QMultiComboBox(QWidget * parent)
  : QComboBox(parent),
    stepValidator(new StepValidator(this))
{
  // Direct call to the setValidator(stepValidator) does not work
  // here because the construction has to be completed in prior.
  QTimer::singleShot(0, this, SLOT(fixme()));
}



LineEdit::LineEdit(QWidget *parent)
  : QLineEdit(parent)
{
  clearButton = new QToolButton(this);
  clearButton->setToolTip("Clear text");
  clearButton->setArrowType(Qt::LeftArrow);
  clearButton->setCursor(Qt::ArrowCursor);
  clearButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
  clearButton->hide();
  connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
  connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateCloseButton(const QString&)));
  int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
  setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(clearButton->sizeHint().width() + frameWidth + 1));
  QSize msz = minimumSizeHint();
  setMinimumSize(qMax(msz.width(), clearButton->sizeHint().height() + frameWidth * 2 + 2),
                 qMax(msz.height(), clearButton->sizeHint().height() + frameWidth * 2 + 2));
}

void LineEdit::resizeEvent(QResizeEvent *) {
  QSize sz = clearButton->sizeHint();
  int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
  clearButton->move(rect().right() - frameWidth - sz.width(),
                    (rect().bottom() + 1 - sz.height())/2);
}

void LineEdit::updateCloseButton(const QString& text) {
  clearButton->setVisible(!text.isEmpty());
}





QHistoryDSB::QHistoryDSB(QWidget * parent) :
  QMDoubleSpinBox(parent),
  history_menu(new QMenu(this))
{
  lineEdit()->installEventFilter(this);
  history_menu->setDisabled(true);
}


bool QHistoryDSB::eventFilter(QObject *obj, QEvent *event) {
  QChildEvent * chev = dynamic_cast<QChildEvent*>(event);
  QMenu * menu=0;
  if ( chev && chev->polished() &&
       (menu = dynamic_cast<QMenu*>(chev->child())) ) {
    QAction * action = new QAction(QString("History"), menu);
    action->setMenu(history_menu);
    QAction * fact = menu->actions().value(0);
    menu->insertAction(fact, action);
  }
  return QDoubleSpinBox::eventFilter(obj,event);
}

void QHistoryDSB::rememberInHistory() {
  history_menu->setEnabled(true);
  QAction * act = new QAction(QString::number(value()), history_menu);
  connect(act, SIGNAL(triggered()), SLOT(execHistory()));
  history_menu->insertAction(lastHistory, act);
  lastHistory = act;
}

void QHistoryDSB::execHistory() {

  QAction * act = dynamic_cast<QAction*> (sender());
  if (!act)
    return;

  bool convok;
  double his=act->text().toDouble(&convok);
  if (!convok)
    return;

  setValue(his);
  emit valueEdited(his);

}














class FilterPVsProxyModel : private QSortFilterProxyModel {
private:
  QStringList searchWords;
  QStringList restrictTo;
  QStringList hideMe;
public:

  FilterPVsProxyModel( KnownPVTable * pvTable , QObject * parent=0) :
    QSortFilterProxyModel(parent) {
    setSourceModel(pvTable);
    setDynamicSortFilter(true);
    setFilterKeyColumn(-1);
    sort(0, Qt::AscendingOrder);
  }
  QAbstractItemModel * aModel() { return this; }

  void setSearch(const QString & str = QString() ) {
    searchWords = str.split(QRegExp("\\s+"));
    searchWords.removeDuplicates();
    searchWords.removeOne("");
    invalidateFilter();
  }

  void setRestricted(const QStringList & lst = QStringList()) {
    restrictTo = lst;
    invalidateFilter();
  }

  void setHidden(const QStringList & lst = QStringList()) {
    hideMe = lst;
    invalidateFilter();
  }


protected:

  bool filterAcceptsRow(int source_row, const QModelIndex & source_parent) const {

    const int column_count = sourceModel()->columnCount(source_parent);
    QString pv = sourceModel()->data(sourceModel()->index(source_row, 0, source_parent)).toString();
    if ( ( ! restrictTo.isEmpty() && ! restrictTo.contains(pv) ) ||
         ( ! hideMe.isEmpty() && hideMe.contains(pv) ) )
      return false;
    for (int column = 0; column < column_count; ++column) {
      QModelIndex source_index = sourceModel()->index(source_row, column, source_parent);
      QString key = sourceModel()->data(source_index).toString();
      bool found = true;
      foreach (QString word, searchWords) {
        found &= (bool) key.contains(word, Qt::CaseInsensitive);
        if (!found)
          break;
      }
      if (found)
        return true;
    }
    return false;

  }

};


class KeyPressEater : public QObject {
public:
  KeyPressEater(QObject * parent) : QObject(parent) {}
protected:
  bool eventFilter(QObject *obj, QEvent *event)  {

    if ( event->type() != QEvent::KeyPress &&
      event->type() != QEvent::KeyRelease &&
             event->type() != QEvent::ShortcutOverride )
      return QObject::eventFilter(obj, event);

    QLineEdit * search = parent()->findChild<QLineEdit*>("search");
    QTableView * pvTable = parent()->findChild<QTableView*>("pvTable");

    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    int key = keyEvent->key();
    QString text = keyEvent->text();


    if ( key == Qt::Key_Enter  ||
         key == Qt::Key_Return ||
         key == Qt::Key_Escape ||
         key == Qt::Key_Tab )
    {
      return QObject::eventFilter(obj, event);
    } else if ( pvTable->hasFocus() &&
              ( ! text.isEmpty() ||
                key == Qt::Key_Left ||
                key == Qt::Key_Right  ) )
    {
      search->setFocus();
      QString stext = search->text();
      if (key== Qt::Key_Backspace)
        search->setText( stext.remove( stext.length()-1, 1) );
      else if ( ! text.isEmpty() ) {
        search->setText( stext + text );
      }
    } else if ( search->hasFocus() &&
                ( key == Qt::Key_Down ||
                  key == Qt::Key_Up )  )
    {
      pvTable->setFocus();
    }

    return QObject::eventFilter(obj, event);

  }
};















const QString KnownPVTable::pvListBaseName = "listOfKnownMotorPVs.txt";



KnownPVTable::KnownPVTable(QObject * parent)
  : QAbstractTableModel(parent)
{
  QStringList listPvs;
  foreach(QString pth, QStringList() << QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)
                                     << QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation) ) {
    QDir dir(pth);
    qDebug() << pth;
    foreach(QString cfg, dir.entryList(QStringList() << pvListBaseName, QDir::Files) ) {
      QFile file(dir.canonicalPath() + QDir::separator() + cfg);
      if ( file.open(QIODevice::ReadOnly | QIODevice::Text) && file.isReadable() ) {
        while (!file.atEnd()) {
          QByteArray line = file.readLine().trimmed();
          if ( ! line.isEmpty() && line.at(0) != '#' )
            addPv(line);
        }
        file.close();
      }
    }
  }
}


QModelIndex KnownPVTable::addPv(const QString& newPv) {
  if (newPv.isEmpty())
    return QModelIndex();
  const QString name = newPv.trimmed() + ".DESC";
  QEpicsPv * pv;
  foreach(pv, knownPVs)
    if (pv->pv() == name)
      return indexOf(pv);
  pv = new QEpicsPv(name, this) ;
  connect(pv, SIGNAL(valueChanged(QVariant)), SLOT(updateData()));
  beginResetModel();
  knownPVs << pv;
  endResetModel();
  return indexOf(pv);
}

QList<QModelIndex> KnownPVTable::addPv(const QStringList & newPvs) {
  QList<QModelIndex> idxs;
  foreach(QString newPv, newPvs)
    idxs << addPv(newPv);
  return idxs;
}

QModelIndex KnownPVTable::indexOf(QEpicsPv* pv) const {
  return knownPVs.contains(pv) ?
         createIndex(knownPVs.indexOf(pv), 0) :
         QModelIndex();
}


int KnownPVTable::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return knownPVs.count();
}

int KnownPVTable::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 2;
}


QVariant KnownPVTable::data(const QModelIndex &index, int role) const {
  if ( ! index.isValid() || index.row() >= knownPVs.count() || index.row() < 0)
    return QVariant();
  QString pv = knownPVs.at(index.row())->pv();
  if (role == Qt::DisplayRole) {
    switch (index.column()) {
      case 0: return pv.remove(".DESC");
      case 1: return knownPVs.at(index.row())->get();
      default: return QVariant();
    }
  } else if (role == Qt::UserRole) {
    return pv.remove(".DESC");
  } else {
    return QVariant();
  }
}


QVariant KnownPVTable::headerData(int section, Qt::Orientation orientation, int role) const {
  if (role != Qt::DisplayRole || orientation != Qt::Horizontal )
    return QVariant();
  switch (section) {
    case 0: return QString("PV");
    case 1: return QString("Description");
    default: return QVariant();
  }
}


void KnownPVTable::updateData() {
  QModelIndex midx = indexOf( (QEpicsPv*) sender() );
  if ( midx.isValid() )
    emit (dataChanged(midx, midx));
}













MotorSelection::MotorSelection(QWidget * parent)
  : QDialog(parent),
  ui(new Ui::MotorSelection),
  knownPVs(new KnownPVTable(this)),
  proxyModel(new FilterPVsProxyModel(knownPVs, this))
{
  ui->setupUi(this);
  ui->pvTable->setModel(proxyModel->aModel());
  ui->pvTable->resizeColumnsToContents();
  installEventFilter(new KeyPressEater(this));
  connect(ui->search,  SIGNAL(textChanged(QString)), SLOT(filterPV(QString)));
  connect(ui->search,  SIGNAL(returnPressed()), SLOT(pvFromSearch()));
  connect(ui->pvTable, SIGNAL(clicked(QModelIndex)), SLOT(clickPV(QModelIndex)));
  connect(ui->pvTable, SIGNAL(doubleClicked(QModelIndex)), SLOT(doubleClickPV(QModelIndex)));
  connect(ui->selectAll, SIGNAL(clicked()), ui->pvTable, SLOT(selectAll()));
  connect(ui->selectNone, SIGNAL(clicked()), ui->pvTable, SLOT(clearSelection()));
  connect(ui->selectInvert, SIGNAL(clicked()), SLOT(selectInvert()));
  connect(ui->accept, SIGNAL(clicked()), SLOT(accept()));
  connect(ui->cancel, SIGNAL(clicked()), SLOT(reject()));
  setSingleSelection();
}


QStringList MotorSelection::selected() {
  QStringList sel;
  foreach(QModelIndex idx, ui->pvTable->selectionModel()->selectedRows())
    sel << ui->pvTable->selectionModel()->model()->data(idx, Qt::DisplayRole).toString();
  return sel;
}

void MotorSelection::setSingleSelection(bool sng) {
  ui->buttons->setVisible(!sng);
  ui->pvTable->setSelectionMode( sng
      ? QAbstractItemView::SingleSelection : QAbstractItemView::MultiSelection);
}

bool MotorSelection::isSingleSelection() const {
  return ui->pvTable->selectionMode() == QAbstractItemView::SingleSelection;
}

void MotorSelection::filterPV(const QString & _text){
  proxyModel->setSearch(_text);
}

void MotorSelection::clickPV(const QModelIndex & index) {
  if (isSingleSelection())
    accept();
}

void MotorSelection::doubleClickPV(const QModelIndex & index) {
  ui->pvTable->clearSelection();
  ui->pvTable->selectRow(index.row());
  accept();
}

void MotorSelection::pvFromSearch(){
  QModelIndex idx = knownPVs->addPv(ui->search->text());
  ui->pvTable->resizeColumnsToContents();
  ui->pvTable->selectionModel()->select(idx, QItemSelectionModel::Select);
  if (isSingleSelection())
    accept();
}

void MotorSelection::selectInvert() {
  QModelIndexList oldsl = ui->pvTable->selectionModel()->selectedIndexes();
  ui->pvTable->selectAll();
  foreach(QModelIndex idx, oldsl)
    ui->pvTable->selectionModel()->select(idx, QItemSelectionModel::Deselect);
}

void MotorSelection::limitSelection(const QStringList& acceptedPvs, bool selectRestricted) {
  knownPVs->addPv(acceptedPvs);
  proxyModel->setRestricted(acceptedPvs);
  if ( ! isSingleSelection() && ! acceptedPvs.isEmpty() && selectRestricted )
    ui->pvTable->selectAll();
}










