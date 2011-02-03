#ifndef INTERBUTT_H
#define INTERBUTT_H

#include <QWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>




/// The widget controlling the motor's position in the UI.
/// Consists of three buttons: move-up, move-down and remove.
class interbutt : public QWidget {

  Q_OBJECT;

public:

  /// Constructor
  /// @param parent Parent of the object.
  interbutt(QWidget *parent = 0);

  /// Destructor
  ~interbutt();

private:
  QHBoxLayout *horizontalLayout; ///< widget's layout
  QToolButton *_remove;         ///< remove button
  QToolButton *_up;             ///< move up button
  QToolButton *_down;           ///< move down button


signals:

  /// Emitted when Up button was pressed.
  /// @param widg this object
  void up(interbutt* widg);

  /// Emitted when Down button was pressed.
  /// @param widg this object
  void down(interbutt* widg);

  /// Emitted when Remove button was pressed.
  /// @param widg this object
  void remove(interbutt* widg);


private slots:

  void on_down_clicked();       ///< Just emits ::down() signal
  void on_up_clicked();         ///< Just emits ::up() signal
  void on_remove_clicked();     ///< Just emits ::remove() signal

};

#endif // INTERBUTT_H
