/*
 * Interface wrapper code.
 *
 * Generated by SIP 4.19.16
 */

#include "sipAPIpyqmotorstack.h"

#line 149 "/usr/share/sip/PyQt5/QtCore/qpycore_qlist.sip"
#include <qlist.h>
#line 12 "./sippyqmotorstackQList0101QCaMotorGUI.cpp"

#line 12 "../qcamotorgui_py//pyqcamotorgui.sip"
#include "qcamotorgui.h"
#line 16 "./sippyqmotorstackQList0101QCaMotorGUI.cpp"


extern "C" {static void assign_QList_0101QCaMotorGUI(void *, SIP_SSIZE_T, void *);}
static void assign_QList_0101QCaMotorGUI(void *sipDst, SIP_SSIZE_T sipDstIdx, void *sipSrc)
{
    reinterpret_cast<QList< ::QCaMotorGUI*> *>(sipDst)[sipDstIdx] = *reinterpret_cast<QList< ::QCaMotorGUI*> *>(sipSrc);
}


extern "C" {static void *array_QList_0101QCaMotorGUI(SIP_SSIZE_T);}
static void *array_QList_0101QCaMotorGUI(SIP_SSIZE_T sipNrElem)
{
    return new QList< ::QCaMotorGUI*>[sipNrElem];
}


extern "C" {static void *copy_QList_0101QCaMotorGUI(const void *, SIP_SSIZE_T);}
static void *copy_QList_0101QCaMotorGUI(const void *sipSrc, SIP_SSIZE_T sipSrcIdx)
{
    return new QList< ::QCaMotorGUI*>(reinterpret_cast<const QList< ::QCaMotorGUI*> *>(sipSrc)[sipSrcIdx]);
}


/* Call the mapped type's destructor. */
extern "C" {static void release_QList_0101QCaMotorGUI(void *, int);}
static void release_QList_0101QCaMotorGUI(void *ptr, int)
{
    delete reinterpret_cast<QList< ::QCaMotorGUI*> *>(ptr);
}



extern "C" {static int convertTo_QList_0101QCaMotorGUI(PyObject *, void **, int *, PyObject *);}
static int convertTo_QList_0101QCaMotorGUI(PyObject *sipPy,void **sipCppPtrV,int *sipIsErr,PyObject *sipTransferObj)
{
    QList< ::QCaMotorGUI*> **sipCppPtr = reinterpret_cast<QList< ::QCaMotorGUI*> **>(sipCppPtrV);

#line 184 "/usr/share/sip/PyQt5/QtCore/qpycore_qlist.sip"
    PyObject *iter = PyObject_GetIter(sipPy);

    if (!sipIsErr)
    {
        PyErr_Clear();
        Py_XDECREF(iter);

        return (iter
#if PY_MAJOR_VERSION < 3
                && !PyString_Check(sipPy)
#endif
                && !PyUnicode_Check(sipPy));
    }

    if (!iter)
    {
        *sipIsErr = 1;

        return 0;
    }

    QList<QCaMotorGUI *> *ql = new QList<QCaMotorGUI *>;
 
    for (Py_ssize_t i = 0; ; ++i)
    {
        PyErr_Clear();
        PyObject *itm = PyIter_Next(iter);

        if (!itm)
        {
            if (PyErr_Occurred())
            {
                delete ql;
                Py_DECREF(iter);
                *sipIsErr = 1;

                return 0;
            }

            break;
        }

        QCaMotorGUI *t = reinterpret_cast<QCaMotorGUI *>(
                sipForceConvertToType(itm, sipType_QCaMotorGUI, sipTransferObj, 0,
                        0, sipIsErr));
 
        if (*sipIsErr)
        {
            PyErr_Format(PyExc_TypeError,
                    "index %zd has type '%s' but 'QCaMotorGUI' is expected", i,
                    sipPyTypeName(Py_TYPE(itm)));

            Py_DECREF(itm);
            delete ql;
            Py_DECREF(iter);

            return 0;
        }

        ql->append(t);

        Py_DECREF(itm);
    }

    Py_DECREF(iter);
 
    *sipCppPtr = ql;
 
    return sipGetState(sipTransferObj);
#line 124 "./sippyqmotorstackQList0101QCaMotorGUI.cpp"
}


extern "C" {static PyObject *convertFrom_QList_0101QCaMotorGUI(void *, PyObject *);}
static PyObject *convertFrom_QList_0101QCaMotorGUI(void *sipCppV, PyObject *sipTransferObj)
{
   QList< ::QCaMotorGUI*> *sipCpp = reinterpret_cast<QList< ::QCaMotorGUI*> *>(sipCppV);

#line 153 "/usr/share/sip/PyQt5/QtCore/qpycore_qlist.sip"
    int gc_enabled = sipEnableGC(0);
    PyObject *l = PyList_New(sipCpp->size());

    if (l)
    {
        for (int i = 0; i < sipCpp->size(); ++i)
        {
            QCaMotorGUI *t = sipCpp->at(i);

            // The explicit (void *) cast allows QCaMotorGUI to be const.
            PyObject *tobj = sipConvertFromType((void *)t, sipType_QCaMotorGUI,
                    sipTransferObj);

            if (!tobj)
            {
                Py_DECREF(l);
                l = 0;

                break;
            }

            PyList_SetItem(l, i, tobj);
        }
    }

    sipEnableGC(gc_enabled);

    return l;
#line 162 "./sippyqmotorstackQList0101QCaMotorGUI.cpp"
}


sipMappedTypeDef sipTypeDef_pyqmotorstack_QList_0101QCaMotorGUI = {
    {
        -1,
        SIP_NULLPTR,
        0,
        SIP_TYPE_MAPPED,
        sipNameNr_22,     /* QList<QCaMotorGUI*> */
        {0},
        0
    },
    {
        -1,
        {0, 0, 1},
        0, 0,
        0, 0,
        0, 0,
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    },
    assign_QList_0101QCaMotorGUI,
    array_QList_0101QCaMotorGUI,
    copy_QList_0101QCaMotorGUI,
    release_QList_0101QCaMotorGUI,
    convertTo_QList_0101QCaMotorGUI,
    convertFrom_QList_0101QCaMotorGUI
};