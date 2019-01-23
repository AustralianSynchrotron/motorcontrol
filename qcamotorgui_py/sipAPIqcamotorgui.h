/*
 * Internal module API header file.
 *
 * Generated by SIP 4.19.12
 */

#ifndef _qcamotorguiAPI_H
#define _qcamotorguiAPI_H

#include <sip.h>

#include <QMetaType>
#include <QThread>

/* These are the qualifiers that are enabled. */
#define SIP_FEATURE_PyQt_MacOSXOnly
#define SIP_FEATURE_PyQt_Process
#define SIP_FEATURE_PyQt_NotBootstrapped
#define SIP_FEATURE_PyQt_Desktop_OpenGL
#define SIP_FEATURE_PyQt_OpenGL
#define SIP_FEATURE_PyQt_RawFont
#define SIP_FEATURE_PyQt_PrintPreviewDialog
#define SIP_FEATURE_PyQt_PrintPreviewWidget
#define SIP_FEATURE_PyQt_Printer
#define SIP_FEATURE_PyQt_PrintDialog
#define SIP_FEATURE_Py_v3
#define SIP_FEATURE_PyQt_qreal_double
#define SIP_FEATURE_PyQt_SSL
#define SIP_FEATURE_PyQt_SessionManager
#define SIP_FEATURE_PyQt_Accessibility
#define SIP_PLATFORM_WS_X11


/*
 * Convenient names to refer to various strings defined in this module.
 * Only the class names are part of the public API.
 */
#define sipNameNr_QCaMotorGUI__ViewMode 0
#define sipName_QCaMotorGUI__ViewMode &sipStrings_qcamotorgui[0]
#define sipNameNr_mouseDoubleClickEvent 22
#define sipName_mouseDoubleClickEvent &sipStrings_qcamotorgui[22]
#define sipNameNr_configsSearchBaseDir 44
#define sipName_configsSearchBaseDir &sipStrings_qcamotorgui[44]
#define sipNameNr_focusPreviousChild 65
#define sipName_focusPreviousChild &sipStrings_qcamotorgui[65]
#define sipNameNr_focusNextPrevChild 84
#define sipName_focusNextPrevChild &sipStrings_qcamotorgui[84]
#define sipNameNr_ioPositionChanged 103
#define sipName_ioPositionChanged &sipStrings_qcamotorgui[103]
#define sipNameNr_destroySubWindows 121
#define sipName_destroySubWindows &sipStrings_qcamotorgui[121]
#define sipNameNr_hasHeightForWidth 139
#define sipName_hasHeightForWidth &sipStrings_qcamotorgui[139]
#define sipNameNr_mouseReleaseEvent 157
#define sipName_mouseReleaseEvent &sipStrings_qcamotorgui[157]
#define sipNameNr_isSignalConnected 175
#define sipName_isSignalConnected &sipStrings_qcamotorgui[175]
#define sipNameNr_senderSignalIndex 193
#define sipName_senderSignalIndex &sipStrings_qcamotorgui[193]
#define sipNameNr_destroyOldWindow 211
#define sipName_destroyOldWindow &sipStrings_qcamotorgui[211]
#define sipNameNr_initializeWindow 228
#define sipName_initializeWindow &sipStrings_qcamotorgui[228]
#define sipNameNr_updateMicroFocus 245
#define sipName_updateMicroFocus &sipStrings_qcamotorgui[245]
#define sipNameNr_contextMenuEvent 262
#define sipName_contextMenuEvent &sipStrings_qcamotorgui[262]
#define sipNameNr_inputMethodEvent 279
#define sipName_inputMethodEvent &sipStrings_qcamotorgui[279]
#define sipNameNr_inputMethodQuery 296
#define sipName_inputMethodQuery &sipStrings_qcamotorgui[296]
#define sipNameNr_disconnectNotify 313
#define sipName_disconnectNotify &sipStrings_qcamotorgui[313]
#define sipNameNr_minimumSizeHint 330
#define sipName_minimumSizeHint &sipStrings_qcamotorgui[330]
#define sipNameNr_mousePressEvent 346
#define sipName_mousePressEvent &sipStrings_qcamotorgui[346]
#define sipNameNr_keyReleaseEvent 362
#define sipName_keyReleaseEvent &sipStrings_qcamotorgui[362]
#define sipNameNr_currentPosition 378
#define sipName_currentPosition &sipStrings_qcamotorgui[378]
#define sipNameNr_deviceTransform 394
#define sipName_deviceTransform &sipStrings_qcamotorgui[394]
#define sipNameNr_internal_format 410
#define sipName_internal_format &sipStrings_qcamotorgui[410]
#define sipNameNr_aspectRatioMode 426
#define sipName_aspectRatioMode &sipStrings_qcamotorgui[426]
#define sipNameNr_pvListBaseName 442
#define sipName_pvListBaseName &sipStrings_qcamotorgui[442]
#define sipNameNr_focusNextChild 457
#define sipName_focusNextChild &sipStrings_qcamotorgui[457]
#define sipNameNr_heightForWidth 472
#define sipName_heightForWidth &sipStrings_qcamotorgui[472]
#define sipNameNr_dragLeaveEvent 487
#define sipName_dragLeaveEvent &sipStrings_qcamotorgui[487]
#define sipNameNr_dragEnterEvent 502
#define sipName_dragEnterEvent &sipStrings_qcamotorgui[502]
#define sipNameNr_mouseMoveEvent 517
#define sipName_mouseMoveEvent &sipStrings_qcamotorgui[517]
#define sipNameNr_changedSignal 532
#define sipName_changedSignal &sipStrings_qcamotorgui[532]
#define sipNameNr_sharedPainter 546
#define sipName_sharedPainter &sipStrings_qcamotorgui[546]
#define sipNameNr_destroyWindow 560
#define sipName_destroyWindow &sipStrings_qcamotorgui[560]
#define sipNameNr_thresholdTime 574
#define sipName_thresholdTime &sipStrings_qcamotorgui[574]
#define sipNameNr_dragMoveEvent 588
#define sipName_dragMoveEvent &sipStrings_qcamotorgui[588]
#define sipNameNr_keyPressEvent 602
#define sipName_keyPressEvent &sipStrings_qcamotorgui[602]
#define sipNameNr_focusOutEvent 616
#define sipName_focusOutEvent &sipStrings_qcamotorgui[616]
#define sipNameNr_transformMode 630
#define sipName_transformMode &sipStrings_qcamotorgui[630]
#define sipNameNr_connectNotify 316
#define sipName_connectNotify &sipStrings_qcamotorgui[316]
#define sipNameNr_sourceRegion 644
#define sipName_sourceRegion &sipStrings_qcamotorgui[644]
#define sipNameNr_targetOffset 657
#define sipName_targetOffset &sipStrings_qcamotorgui[657]
#define sipNameNr_midLineWidth 670
#define sipName_midLineWidth &sipStrings_qcamotorgui[670]
#define sipNameNr_focusInEvent 683
#define sipName_focusInEvent &sipStrings_qcamotorgui[683]
#define sipNameNr_boundingRect 696
#define sipName_boundingRect &sipStrings_qcamotorgui[696]
#define sipNameNr_showPvSetup 709
#define sipName_showPvSetup &sipStrings_qcamotorgui[709]
#define sipNameNr_setupButton 721
#define sipName_setupButton &sipStrings_qcamotorgui[721]
#define sipNameNr_QCaMotorGUI 733
#define sipName_QCaMotorGUI &sipStrings_qcamotorgui[733]
#define sipNameNr_initPainter 745
#define sipName_initPainter &sipStrings_qcamotorgui[745]
#define sipNameNr_nativeEvent 757
#define sipName_nativeEvent &sipStrings_qcamotorgui[757]
#define sipNameNr_actionEvent 769
#define sipName_actionEvent &sipStrings_qcamotorgui[769]
#define sipNameNr_setViewMode 781
#define sipName_setViewMode &sipStrings_qcamotorgui[781]
#define sipNameNr_changeEvent 793
#define sipName_changeEvent &sipStrings_qcamotorgui[793]
#define sipNameNr_tabletEvent 805
#define sipName_tabletEvent &sipStrings_qcamotorgui[805]
#define sipNameNr_matchPolicy 817
#define sipName_matchPolicy &sipStrings_qcamotorgui[817]
#define sipNameNr_resizeEvent 829
#define sipName_resizeEvent &sipStrings_qcamotorgui[829]
#define sipNameNr_paintEngine 841
#define sipName_paintEngine &sipStrings_qcamotorgui[841]
#define sipNameNr_customEvent 853
#define sipName_customEvent &sipStrings_qcamotorgui[853]
#define sipNameNr_eventFilter 865
#define sipName_eventFilter &sipStrings_qcamotorgui[865]
#define sipNameNr_qcamotorgui 877
#define sipName_qcamotorgui &sipStrings_qcamotorgui[877]
#define sipNameNr_configsExt 889
#define sipName_configsExt &sipStrings_qcamotorgui[889]
#define sipNameNr_enterEvent 900
#define sipName_enterEvent &sipStrings_qcamotorgui[900]
#define sipNameNr_leaveEvent 911
#define sipName_leaveEvent &sipStrings_qcamotorgui[911]
#define sipNameNr_constraint 922
#define sipName_constraint &sipStrings_qcamotorgui[922]
#define sipNameNr_closeEvent 933
#define sipName_closeEvent &sipStrings_qcamotorgui[933]
#define sipNameNr_repeatTime 944
#define sipName_repeatTime &sipStrings_qcamotorgui[944]
#define sipNameNr_wheelEvent 955
#define sipName_wheelEvent &sipStrings_qcamotorgui[955]
#define sipNameNr_columnSpan 966
#define sipName_columnSpan &sipStrings_qcamotorgui[966]
#define sipNameNr_paintEvent 977
#define sipName_paintEvent &sipStrings_qcamotorgui[977]
#define sipNameNr_genMipMaps 988
#define sipName_genMipMaps &sipStrings_qcamotorgui[988]
#define sipNameNr_setVisible 999
#define sipName_setVisible &sipStrings_qcamotorgui[999]
#define sipNameNr_childEvent 1010
#define sipName_childEvent &sipStrings_qcamotorgui[1010]
#define sipNameNr_timerEvent 1021
#define sipName_timerEvent &sipStrings_qcamotorgui[1021]
#define sipNameNr_showSetup 1032
#define sipName_showSetup &sipStrings_qcamotorgui[1032]
#define sipNameNr_dropEvent 1042
#define sipName_dropEvent &sipStrings_qcamotorgui[1042]
#define sipNameNr_hideEvent 1052
#define sipName_hideEvent &sipStrings_qcamotorgui[1052]
#define sipNameNr_showEvent 1062
#define sipName_showEvent &sipStrings_qcamotorgui[1062]
#define sipNameNr_moveEvent 1072
#define sipName_moveEvent &sipStrings_qcamotorgui[1072]
#define sipNameNr_operation 1082
#define sipName_operation &sipStrings_qcamotorgui[1082]
#define sipNameNr_lineWidth 1092
#define sipName_lineWidth &sipStrings_qcamotorgui[1092]
#define sipNameNr_directory 1102
#define sipName_directory &sipStrings_qcamotorgui[1102]
#define sipNameNr_alignment 1112
#define sipName_alignment &sipStrings_qcamotorgui[1112]
#define sipNameNr_receivers 1122
#define sipName_receivers &sipStrings_qcamotorgui[1122]
#define sipNameNr_precision 1132
#define sipName_precision &sipStrings_qcamotorgui[1132]
#define sipNameNr_ViewMode 13
#define sipName_ViewMode &sipStrings_qcamotorgui[13]
#define sipNameNr_shortcut 1142
#define sipName_shortcut &sipStrings_qcamotorgui[1142]
#define sipNameNr_userData 1151
#define sipName_userData &sipStrings_qcamotorgui[1151]
#define sipNameNr_sizeHint 1160
#define sipName_sizeHint &sipStrings_qcamotorgui[1160]
#define sipNameNr_fillRule 1169
#define sipName_fillRule &sipStrings_qcamotorgui[1169]
#define sipNameNr_tabArray 1178
#define sipName_tabArray &sipStrings_qcamotorgui[1178]
#define sipNameNr_tabStops 1187
#define sipName_tabStops &sipStrings_qcamotorgui[1187]
#define sipNameNr_nameType 1196
#define sipName_nameType &sipStrings_qcamotorgui[1196]
#define sipNameNr_position 1205
#define sipName_position &sipStrings_qcamotorgui[1205]
#define sipNameNr_property 1214
#define sipName_property &sipStrings_qcamotorgui[1214]
#define sipNameNr_yMargin 1223
#define sipName_yMargin &sipStrings_qcamotorgui[1223]
#define sipNameNr_xMargin 1231
#define sipName_xMargin &sipStrings_qcamotorgui[1231]
#define sipNameNr_rowSpan 1239
#define sipName_rowSpan &sipStrings_qcamotorgui[1239]
#define sipNameNr_exposed 1247
#define sipName_exposed &sipStrings_qcamotorgui[1247]
#define sipNameNr_buffers 1255
#define sipName_buffers &sipStrings_qcamotorgui[1255]
#define sipNameNr_sources 1263
#define sipName_sources &sipStrings_qcamotorgui[1263]
#define sipNameNr_destroy 1271
#define sipName_destroy &sipStrings_qcamotorgui[1271]
#define sipNameNr_quality 1279
#define sipName_quality &sipStrings_qcamotorgui[1279]
#define sipNameNr_devType 1287
#define sipName_devType &sipStrings_qcamotorgui[1287]
#define sipNameNr_filters 1295
#define sipName_filters &sipStrings_qcamotorgui[1295]
#define sipNameNr_enabled 1303
#define sipName_enabled &sipStrings_qcamotorgui[1303]
#define sipNameNr_options 1311
#define sipName_options &sipStrings_qcamotorgui[1311]
#define sipNameNr_CONFIG 1319
#define sipName_CONFIG &sipStrings_qcamotorgui[1319]
#define sipNameNr_sunken 1326
#define sipName_sunken &sipStrings_qcamotorgui[1326]
#define sipNameNr_layers 1333
#define sipName_layers &sipStrings_qcamotorgui[1333]
#define sipNameNr_stride 1340
#define sipName_stride &sipStrings_qcamotorgui[1340]
#define sipNameNr_metric 1347
#define sipName_metric &sipStrings_qcamotorgui[1347]
#define sipNameNr_window 1354
#define sipName_window &sipStrings_qcamotorgui[1354]
#define sipNameNr_create 1361
#define sipName_create &sipStrings_qcamotorgui[1361]
#define sipNameNr_proper 1368
#define sipName_proper &sipStrings_qcamotorgui[1368]
#define sipNameNr_sender 1375
#define sipName_sender &sipStrings_qcamotorgui[1375]
#define sipNameNr_value9 1382
#define sipName_value9 &sipStrings_qcamotorgui[1382]
#define sipNameNr_value8 1389
#define sipName_value8 &sipStrings_qcamotorgui[1389]
#define sipNameNr_value7 1396
#define sipName_value7 &sipStrings_qcamotorgui[1396]
#define sipNameNr_value6 1403
#define sipName_value6 &sipStrings_qcamotorgui[1403]
#define sipNameNr_value5 1410
#define sipName_value5 &sipStrings_qcamotorgui[1410]
#define sipNameNr_value4 1417
#define sipName_value4 &sipStrings_qcamotorgui[1417]
#define sipNameNr_value3 1424
#define sipName_value3 &sipStrings_qcamotorgui[1424]
#define sipNameNr_value2 1431
#define sipName_value2 &sipStrings_qcamotorgui[1431]
#define sipNameNr_value1 1438
#define sipName_value1 &sipStrings_qcamotorgui[1438]
#define sipNameNr_value0 1445
#define sipName_value0 &sipStrings_qcamotorgui[1445]
#define sipNameNr_system 1452
#define sipName_system &sipStrings_qcamotorgui[1452]
#define sipNameNr_symbol 1459
#define sipName_symbol &sipStrings_qcamotorgui[1459]
#define sipNameNr_suffix 1466
#define sipName_suffix &sipStrings_qcamotorgui[1466]
#define sipNameNr_offset 1473
#define sipName_offset &sipStrings_qcamotorgui[1473]
#define sipNameNr_prefix 1480
#define sipName_prefix &sipStrings_qcamotorgui[1480]
#define sipNameNr_filter 1487
#define sipName_filter &sipStrings_qcamotorgui[1487]
#define sipNameNr_option 1494
#define sipName_option &sipStrings_qcamotorgui[1494]
#define sipNameNr_locale 1501
#define sipName_locale &sipStrings_qcamotorgui[1501]
#define sipNameNr_format 419
#define sipName_format &sipStrings_qcamotorgui[419]
#define sipNameNr_column 1508
#define sipName_column &sipStrings_qcamotorgui[1508]
#define sipNameNr_object 1515
#define sipName_object &sipStrings_qcamotorgui[1515]
#define sipNameNr_parent 1522
#define sipName_parent &sipStrings_qcamotorgui[1522]
#define sipNameNr_motor 1529
#define sipName_motor &sipStrings_qcamotorgui[1529]
#define sipNameNr_EPICS 1535
#define sipName_EPICS &sipStrings_qcamotorgui[1535]
#define sipNameNr_COMFO 1541
#define sipName_COMFO &sipStrings_qcamotorgui[1541]
#define sipNameNr_SETPV 1547
#define sipName_SETPV &sipStrings_qcamotorgui[1547]
#define sipNameNr_brush 1553
#define sipName_brush &sipStrings_qcamotorgui[1553]
#define sipNameNr_types 1559
#define sipName_types &sipStrings_qcamotorgui[1559]
#define sipNameNr_order 1565
#define sipName_order &sipStrings_qcamotorgui[1565]
#define sipNameNr_roles 1571
#define sipName_roles &sipStrings_qcamotorgui[1571]
#define sipNameNr_flags 1577
#define sipName_flags &sipStrings_qcamotorgui[1577]
#define sipNameNr_event 1583
#define sipName_event &sipStrings_qcamotorgui[1583]
#define sipNameNr_msecs 1589
#define sipName_msecs &sipStrings_qcamotorgui[1589]
#define sipNameNr_state 1595
#define sipName_state &sipStrings_qcamotorgui[1595]
#define sipNameNr_MINI 1601
#define sipName_MINI &sipStrings_qcamotorgui[1601]
#define sipNameNr_lock 1606
#define sipName_lock &sipStrings_qcamotorgui[1606]
#define sipNameNr_mode 1611
#define sipName_mode &sipStrings_qcamotorgui[1611]
#define sipNameNr_name 1616
#define sipName_name &sipStrings_qcamotorgui[1616]
#define sipNameNr_base 1621
#define sipName_base &sipStrings_qcamotorgui[1621]
#define sipNameNr_fill 1626
#define sipName_fill &sipStrings_qcamotorgui[1626]
#define sipNameNr_from 1631
#define sipName_from &sipStrings_qcamotorgui[1631]
#define sipNameNr_sort 1636
#define sipName_sort &sipStrings_qcamotorgui[1636]
#define sipNameNr_pen 1641
#define sipName_pen &sipStrings_qcamotorgui[1641]
#define sipNameNr_pid 1645
#define sipName_pid &sipStrings_qcamotorgui[1645]
#define sipNameNr_pos 1649
#define sipName_pos &sipStrings_qcamotorgui[1649]
#define sipNameNr_sw 1653
#define sipName_sw &sipStrings_qcamotorgui[1653]
#define sipNameNr_sh 1556
#define sipName_sh &sipStrings_qcamotorgui[1556]
#define sipNameNr_sy 1656
#define sipName_sy &sipStrings_qcamotorgui[1656]
#define sipNameNr_sx 1659
#define sipName_sx &sipStrings_qcamotorgui[1659]
#define sipNameNr_at 423
#define sipName_at &sipStrings_qcamotorgui[423]

#define sipMalloc                   sipAPI_qcamotorgui->api_malloc
#define sipFree                     sipAPI_qcamotorgui->api_free
#define sipBuildResult              sipAPI_qcamotorgui->api_build_result
#define sipCallMethod               sipAPI_qcamotorgui->api_call_method
#define sipCallProcedureMethod      sipAPI_qcamotorgui->api_call_procedure_method
#define sipCallErrorHandler         sipAPI_qcamotorgui->api_call_error_handler
#define sipParseResultEx            sipAPI_qcamotorgui->api_parse_result_ex
#define sipParseResult              sipAPI_qcamotorgui->api_parse_result
#define sipParseArgs                sipAPI_qcamotorgui->api_parse_args
#define sipParseKwdArgs             sipAPI_qcamotorgui->api_parse_kwd_args
#define sipParsePair                sipAPI_qcamotorgui->api_parse_pair
#define sipInstanceDestroyed        sipAPI_qcamotorgui->api_instance_destroyed
#define sipInstanceDestroyedEx      sipAPI_qcamotorgui->api_instance_destroyed_ex
#define sipConvertFromSequenceIndex sipAPI_qcamotorgui->api_convert_from_sequence_index
#define sipConvertFromSliceObject   sipAPI_qcamotorgui->api_convert_from_slice_object
#define sipConvertFromVoidPtr       sipAPI_qcamotorgui->api_convert_from_void_ptr
#define sipConvertToVoidPtr         sipAPI_qcamotorgui->api_convert_to_void_ptr
#define sipAddException             sipAPI_qcamotorgui->api_add_exception
#define sipNoFunction               sipAPI_qcamotorgui->api_no_function
#define sipNoMethod                 sipAPI_qcamotorgui->api_no_method
#define sipAbstractMethod           sipAPI_qcamotorgui->api_abstract_method
#define sipBadClass                 sipAPI_qcamotorgui->api_bad_class
#define sipBadCatcherResult         sipAPI_qcamotorgui->api_bad_catcher_result
#define sipBadCallableArg           sipAPI_qcamotorgui->api_bad_callable_arg
#define sipBadOperatorArg           sipAPI_qcamotorgui->api_bad_operator_arg
#define sipTrace                    sipAPI_qcamotorgui->api_trace
#define sipTransferBack             sipAPI_qcamotorgui->api_transfer_back
#define sipTransferTo               sipAPI_qcamotorgui->api_transfer_to
#define sipTransferBreak            sipAPI_qcamotorgui->api_transfer_break
#define sipSimpleWrapper_Type       sipAPI_qcamotorgui->api_simplewrapper_type
#define sipWrapper_Type             sipAPI_qcamotorgui->api_wrapper_type
#define sipWrapperType_Type         sipAPI_qcamotorgui->api_wrappertype_type
#define sipVoidPtr_Type             sipAPI_qcamotorgui->api_voidptr_type
#define sipGetPyObject              sipAPI_qcamotorgui->api_get_pyobject
#define sipGetAddress               sipAPI_qcamotorgui->api_get_address
#define sipGetMixinAddress          sipAPI_qcamotorgui->api_get_mixin_address
#define sipGetCppPtr                sipAPI_qcamotorgui->api_get_cpp_ptr
#define sipGetComplexCppPtr         sipAPI_qcamotorgui->api_get_complex_cpp_ptr
#define sipIsPyMethod               sipAPI_qcamotorgui->api_is_py_method
#define sipCallHook                 sipAPI_qcamotorgui->api_call_hook
#define sipEndThread                sipAPI_qcamotorgui->api_end_thread
#define sipConnectRx                sipAPI_qcamotorgui->api_connect_rx
#define sipDisconnectRx             sipAPI_qcamotorgui->api_disconnect_rx
#define sipRaiseUnknownException    sipAPI_qcamotorgui->api_raise_unknown_exception
#define sipRaiseTypeException       sipAPI_qcamotorgui->api_raise_type_exception
#define sipBadLengthForSlice        sipAPI_qcamotorgui->api_bad_length_for_slice
#define sipAddTypeInstance          sipAPI_qcamotorgui->api_add_type_instance
#define sipFreeSipslot              sipAPI_qcamotorgui->api_free_sipslot
#define sipSameSlot                 sipAPI_qcamotorgui->api_same_slot
#define sipPySlotExtend             sipAPI_qcamotorgui->api_pyslot_extend
#define sipConvertRx                sipAPI_qcamotorgui->api_convert_rx
#define sipAddDelayedDtor           sipAPI_qcamotorgui->api_add_delayed_dtor
#define sipCanConvertToType         sipAPI_qcamotorgui->api_can_convert_to_type
#define sipConvertToType            sipAPI_qcamotorgui->api_convert_to_type
#define sipForceConvertToType       sipAPI_qcamotorgui->api_force_convert_to_type
#define sipCanConvertToEnum         sipAPI_qcamotorgui->api_can_convert_to_enum
#define sipConvertToEnum            sipAPI_qcamotorgui->api_convert_to_enum
#define sipConvertToBool            sipAPI_qcamotorgui->api_convert_to_bool
#define sipReleaseType              sipAPI_qcamotorgui->api_release_type
#define sipConvertFromType          sipAPI_qcamotorgui->api_convert_from_type
#define sipConvertFromNewType       sipAPI_qcamotorgui->api_convert_from_new_type
#define sipConvertFromNewPyType     sipAPI_qcamotorgui->api_convert_from_new_pytype
#define sipConvertFromEnum          sipAPI_qcamotorgui->api_convert_from_enum
#define sipGetState                 sipAPI_qcamotorgui->api_get_state
#define sipExportSymbol             sipAPI_qcamotorgui->api_export_symbol
#define sipImportSymbol             sipAPI_qcamotorgui->api_import_symbol
#define sipFindType                 sipAPI_qcamotorgui->api_find_type
#define sipFindNamedEnum            sipAPI_qcamotorgui->api_find_named_enum
#define sipBytes_AsChar             sipAPI_qcamotorgui->api_bytes_as_char
#define sipBytes_AsString           sipAPI_qcamotorgui->api_bytes_as_string
#define sipString_AsASCIIChar       sipAPI_qcamotorgui->api_string_as_ascii_char
#define sipString_AsASCIIString     sipAPI_qcamotorgui->api_string_as_ascii_string
#define sipString_AsLatin1Char      sipAPI_qcamotorgui->api_string_as_latin1_char
#define sipString_AsLatin1String    sipAPI_qcamotorgui->api_string_as_latin1_string
#define sipString_AsUTF8Char        sipAPI_qcamotorgui->api_string_as_utf8_char
#define sipString_AsUTF8String      sipAPI_qcamotorgui->api_string_as_utf8_string
#define sipUnicode_AsWChar          sipAPI_qcamotorgui->api_unicode_as_wchar
#define sipUnicode_AsWString        sipAPI_qcamotorgui->api_unicode_as_wstring
#define sipConvertFromConstVoidPtr  sipAPI_qcamotorgui->api_convert_from_const_void_ptr
#define sipConvertFromVoidPtrAndSize    sipAPI_qcamotorgui->api_convert_from_void_ptr_and_size
#define sipConvertFromConstVoidPtrAndSize   sipAPI_qcamotorgui->api_convert_from_const_void_ptr_and_size
#define sipInvokeSlot               sipAPI_qcamotorgui->api_invoke_slot
#define sipInvokeSlotEx             sipAPI_qcamotorgui->api_invoke_slot_ex
#define sipSaveSlot                 sipAPI_qcamotorgui->api_save_slot
#define sipClearAnySlotReference    sipAPI_qcamotorgui->api_clear_any_slot_reference
#define sipVisitSlot                sipAPI_qcamotorgui->api_visit_slot
#define sipWrappedTypeName(wt)      ((wt)->wt_td->td_cname)
#define sipDeprecated               sipAPI_qcamotorgui->api_deprecated
#define sipGetReference             sipAPI_qcamotorgui->api_get_reference
#define sipKeepReference            sipAPI_qcamotorgui->api_keep_reference
#define sipRegisterProxyResolver    sipAPI_qcamotorgui->api_register_proxy_resolver
#define sipRegisterPyType           sipAPI_qcamotorgui->api_register_py_type
#define sipTypeFromPyTypeObject     sipAPI_qcamotorgui->api_type_from_py_type_object
#define sipTypeScope                sipAPI_qcamotorgui->api_type_scope
#define sipResolveTypedef           sipAPI_qcamotorgui->api_resolve_typedef
#define sipRegisterAttributeGetter  sipAPI_qcamotorgui->api_register_attribute_getter
#define sipIsAPIEnabled             sipAPI_qcamotorgui->api_is_api_enabled
#define sipSetDestroyOnExit         sipAPI_qcamotorgui->api_set_destroy_on_exit
#define sipEnableAutoconversion     sipAPI_qcamotorgui->api_enable_autoconversion
#define sipEnableOverflowChecking   sipAPI_qcamotorgui->api_enable_overflow_checking
#define sipInitMixin                sipAPI_qcamotorgui->api_init_mixin
#define sipExportModule             sipAPI_qcamotorgui->api_export_module
#define sipInitModule               sipAPI_qcamotorgui->api_init_module
#define sipGetInterpreter           sipAPI_qcamotorgui->api_get_interpreter
#define sipSetNewUserTypeHandler    sipAPI_qcamotorgui->api_set_new_user_type_handler
#define sipSetTypeUserData          sipAPI_qcamotorgui->api_set_type_user_data
#define sipGetTypeUserData          sipAPI_qcamotorgui->api_get_type_user_data
#define sipPyTypeDict               sipAPI_qcamotorgui->api_py_type_dict
#define sipPyTypeName               sipAPI_qcamotorgui->api_py_type_name
#define sipGetCFunction             sipAPI_qcamotorgui->api_get_c_function
#define sipGetMethod                sipAPI_qcamotorgui->api_get_method
#define sipFromMethod               sipAPI_qcamotorgui->api_from_method
#define sipGetDate                  sipAPI_qcamotorgui->api_get_date
#define sipFromDate                 sipAPI_qcamotorgui->api_from_date
#define sipGetDateTime              sipAPI_qcamotorgui->api_get_datetime
#define sipFromDateTime             sipAPI_qcamotorgui->api_from_datetime
#define sipGetTime                  sipAPI_qcamotorgui->api_get_time
#define sipFromTime                 sipAPI_qcamotorgui->api_from_time
#define sipIsUserType               sipAPI_qcamotorgui->api_is_user_type
#define sipGetFrame                 sipAPI_qcamotorgui->api_get_frame
#define sipCheckPluginForType       sipAPI_qcamotorgui->api_check_plugin_for_type
#define sipUnicodeNew               sipAPI_qcamotorgui->api_unicode_new
#define sipUnicodeWrite             sipAPI_qcamotorgui->api_unicode_write
#define sipUnicodeData              sipAPI_qcamotorgui->api_unicode_data
#define sipGetBufferInfo            sipAPI_qcamotorgui->api_get_buffer_info
#define sipReleaseBufferInfo        sipAPI_qcamotorgui->api_release_buffer_info
#define sipIsOwnedByPython          sipAPI_qcamotorgui->api_is_owned_by_python
#define sipIsDerivedClass           sipAPI_qcamotorgui->api_is_derived_class
#define sipGetUserObject            sipAPI_qcamotorgui->api_get_user_object
#define sipSetUserObject            sipAPI_qcamotorgui->api_set_user_object
#define sipRegisterEventHandler     sipAPI_qcamotorgui->api_register_event_handler
#define sipLong_AsChar              sipAPI_qcamotorgui->api_long_as_char
#define sipLong_AsSignedChar        sipAPI_qcamotorgui->api_long_as_signed_char
#define sipLong_AsUnsignedChar      sipAPI_qcamotorgui->api_long_as_unsigned_char
#define sipLong_AsShort             sipAPI_qcamotorgui->api_long_as_short
#define sipLong_AsUnsignedShort     sipAPI_qcamotorgui->api_long_as_unsigned_short
#define sipLong_AsInt               sipAPI_qcamotorgui->api_long_as_int
#define sipLong_AsUnsignedInt       sipAPI_qcamotorgui->api_long_as_unsigned_int
#define sipLong_AsLong              sipAPI_qcamotorgui->api_long_as_long
#define sipLong_AsUnsignedLong      sipAPI_qcamotorgui->api_long_as_unsigned_long
#define sipLong_AsLongLong          sipAPI_qcamotorgui->api_long_as_long_long
#define sipLong_AsUnsignedLongLong  sipAPI_qcamotorgui->api_long_as_unsigned_long_long

/* These are deprecated. */
#define sipMapStringToClass         sipAPI_qcamotorgui->api_map_string_to_class
#define sipMapIntToClass            sipAPI_qcamotorgui->api_map_int_to_class
#define sipFindClass                sipAPI_qcamotorgui->api_find_class
#define sipFindMappedType           sipAPI_qcamotorgui->api_find_mapped_type
#define sipConvertToArray           sipAPI_qcamotorgui->api_convert_to_array
#define sipConvertToTypedArray      sipAPI_qcamotorgui->api_convert_to_typed_array
#define sipEnableGC                 sipAPI_qcamotorgui->api_enable_gc
#define sipPrintObject              sipAPI_qcamotorgui->api_print_object
#define sipWrapper_Check(w)         PyObject_TypeCheck((w), sipAPI_qcamotorgui->api_wrapper_type)
#define sipGetWrapper(p, wt)        sipGetPyObject((p), (wt)->wt_td)
#define sipReleaseInstance(p, wt, s)    sipReleaseType((p), (wt)->wt_td, (s))
#define sipReleaseMappedType        sipReleaseType
#define sipCanConvertToInstance(o, wt, f)   sipCanConvertToType((o), (wt)->wt_td, (f))
#define sipCanConvertToMappedType   sipCanConvertToType
#define sipConvertToInstance(o, wt, t, f, s, e)     sipConvertToType((o), (wt)->wt_td, (t), (f), (s), (e))
#define sipConvertToMappedType      sipConvertToType
#define sipForceConvertToInstance(o, wt, t, f, s, e)    sipForceConvertToType((o), (wt)->wt_td, (t), (f), (s), (e))
#define sipForceConvertToMappedType sipForceConvertToType
#define sipConvertFromInstance(p, wt, t)    sipConvertFromType((p), (wt)->wt_td, (t))
#define sipConvertFromMappedType    sipConvertFromType
#define sipConvertFromNamedEnum(v, pt)  sipConvertFromEnum((v), ((sipEnumTypeObject *)(pt))->type)
#define sipConvertFromNewInstance(p, wt, t) sipConvertFromNewType((p), (wt)->wt_td, (t))

/* The strings used by this module. */
extern const char sipStrings_qcamotorgui[];

#define sipType_QCaMotorGUI sipExportedTypes_qcamotorgui[0]
#define sipClass_QCaMotorGUI sipExportedTypes_qcamotorgui[0]->u.td_wrapper_type

#define sipType_QCaMotorGUI_ViewMode sipExportedTypes_qcamotorgui[1]
#define sipEnum_QCaMotorGUI_ViewMode sipExportedTypes_qcamotorgui[1]->u.td_py_type

extern sipClassTypeDef sipTypeDef_qcamotorgui_QCaMotorGUI;

/* The SIP API, this module's API and the APIs of any imported modules. */
extern const sipAPIDef *sipAPI_qcamotorgui;
extern sipExportedModuleDef sipModuleAPI_qcamotorgui;
extern sipTypeDef *sipExportedTypes_qcamotorgui[];

#define sipType_Qt_InputMethodQuery sipImportedTypes_qcamotorgui_QtCore[9].it_td
#define sipEnum_Qt_InputMethodQuery sipImportedTypes_qcamotorgui_QtCore[9].it_td->u.td_py_type

#define sipType_QObject sipImportedTypes_qcamotorgui_QtCore[4].it_td
#define sipClass_QObject sipImportedTypes_qcamotorgui_QtCore[4].it_td->u.td_wrapper_type

#define sipType_QByteArray sipImportedTypes_qcamotorgui_QtCore[0].it_td
#define sipClass_QByteArray sipImportedTypes_qcamotorgui_QtCore[0].it_td->u.td_wrapper_type

#define sipType_QEvent sipImportedTypes_qcamotorgui_QtCore[2].it_td
#define sipClass_QEvent sipImportedTypes_qcamotorgui_QtCore[2].it_td->u.td_wrapper_type

#define sipType_QTimerEvent sipImportedTypes_qcamotorgui_QtCore[7].it_td
#define sipClass_QTimerEvent sipImportedTypes_qcamotorgui_QtCore[7].it_td->u.td_wrapper_type

#define sipType_QChildEvent sipImportedTypes_qcamotorgui_QtCore[1].it_td
#define sipClass_QChildEvent sipImportedTypes_qcamotorgui_QtCore[1].it_td->u.td_wrapper_type

#define sipType_QMetaMethod sipImportedTypes_qcamotorgui_QtCore[3].it_td
#define sipClass_QMetaMethod sipImportedTypes_qcamotorgui_QtCore[3].it_td->u.td_wrapper_type

#define sipType_QSize sipImportedTypes_qcamotorgui_QtCore[5].it_td
#define sipClass_QSize sipImportedTypes_qcamotorgui_QtCore[5].it_td->u.td_wrapper_type

#define sipType_QVariant sipImportedTypes_qcamotorgui_QtCore[8].it_td
#define sipClass_QVariant sipImportedTypes_qcamotorgui_QtCore[8].it_td->u.td_wrapper_type

#define sipType_QString sipImportedTypes_qcamotorgui_QtCore[6].it_td

#define sipType_quintptr sipImportedTypes_qcamotorgui_QtCore[10].it_td
extern sipImportedTypeDef sipImportedTypes_qcamotorgui_QtCore[];
extern sipImportedVirtErrorHandlerDef sipImportedVirtErrorHandlers_qcamotorgui_QtCore[];

#define sipType_QPaintDevice sipImportedTypes_qcamotorgui_QtGui[13].it_td
#define sipClass_QPaintDevice sipImportedTypes_qcamotorgui_QtGui[13].it_td->u.td_wrapper_type

#define sipType_QPaintDevice_PaintDeviceMetric sipImportedTypes_qcamotorgui_QtGui[14].it_td
#define sipEnum_QPaintDevice_PaintDeviceMetric sipImportedTypes_qcamotorgui_QtGui[14].it_td->u.td_py_type

#define sipType_QMouseEvent sipImportedTypes_qcamotorgui_QtGui[11].it_td
#define sipClass_QMouseEvent sipImportedTypes_qcamotorgui_QtGui[11].it_td->u.td_wrapper_type

#define sipType_QWheelEvent sipImportedTypes_qcamotorgui_QtGui[21].it_td
#define sipClass_QWheelEvent sipImportedTypes_qcamotorgui_QtGui[21].it_td->u.td_wrapper_type

#define sipType_QTabletEvent sipImportedTypes_qcamotorgui_QtGui[20].it_td
#define sipClass_QTabletEvent sipImportedTypes_qcamotorgui_QtGui[20].it_td->u.td_wrapper_type

#define sipType_QKeyEvent sipImportedTypes_qcamotorgui_QtGui[10].it_td
#define sipClass_QKeyEvent sipImportedTypes_qcamotorgui_QtGui[10].it_td->u.td_wrapper_type

#define sipType_QFocusEvent sipImportedTypes_qcamotorgui_QtGui[7].it_td
#define sipClass_QFocusEvent sipImportedTypes_qcamotorgui_QtGui[7].it_td->u.td_wrapper_type

#define sipType_QPaintEvent sipImportedTypes_qcamotorgui_QtGui[16].it_td
#define sipClass_QPaintEvent sipImportedTypes_qcamotorgui_QtGui[16].it_td->u.td_wrapper_type

#define sipType_QMoveEvent sipImportedTypes_qcamotorgui_QtGui[12].it_td
#define sipClass_QMoveEvent sipImportedTypes_qcamotorgui_QtGui[12].it_td->u.td_wrapper_type

#define sipType_QResizeEvent sipImportedTypes_qcamotorgui_QtGui[18].it_td
#define sipClass_QResizeEvent sipImportedTypes_qcamotorgui_QtGui[18].it_td->u.td_wrapper_type

#define sipType_QCloseEvent sipImportedTypes_qcamotorgui_QtGui[1].it_td
#define sipClass_QCloseEvent sipImportedTypes_qcamotorgui_QtGui[1].it_td->u.td_wrapper_type

#define sipType_QShowEvent sipImportedTypes_qcamotorgui_QtGui[19].it_td
#define sipClass_QShowEvent sipImportedTypes_qcamotorgui_QtGui[19].it_td->u.td_wrapper_type

#define sipType_QHideEvent sipImportedTypes_qcamotorgui_QtGui[8].it_td
#define sipClass_QHideEvent sipImportedTypes_qcamotorgui_QtGui[8].it_td->u.td_wrapper_type

#define sipType_QContextMenuEvent sipImportedTypes_qcamotorgui_QtGui[2].it_td
#define sipClass_QContextMenuEvent sipImportedTypes_qcamotorgui_QtGui[2].it_td->u.td_wrapper_type

#define sipType_QInputMethodEvent sipImportedTypes_qcamotorgui_QtGui[9].it_td
#define sipClass_QInputMethodEvent sipImportedTypes_qcamotorgui_QtGui[9].it_td->u.td_wrapper_type

#define sipType_QDropEvent sipImportedTypes_qcamotorgui_QtGui[6].it_td
#define sipClass_QDropEvent sipImportedTypes_qcamotorgui_QtGui[6].it_td->u.td_wrapper_type

#define sipType_QDragMoveEvent sipImportedTypes_qcamotorgui_QtGui[5].it_td
#define sipClass_QDragMoveEvent sipImportedTypes_qcamotorgui_QtGui[5].it_td->u.td_wrapper_type

#define sipType_QDragEnterEvent sipImportedTypes_qcamotorgui_QtGui[3].it_td
#define sipClass_QDragEnterEvent sipImportedTypes_qcamotorgui_QtGui[3].it_td->u.td_wrapper_type

#define sipType_QDragLeaveEvent sipImportedTypes_qcamotorgui_QtGui[4].it_td
#define sipClass_QDragLeaveEvent sipImportedTypes_qcamotorgui_QtGui[4].it_td->u.td_wrapper_type

#define sipType_QActionEvent sipImportedTypes_qcamotorgui_QtGui[0].it_td
#define sipClass_QActionEvent sipImportedTypes_qcamotorgui_QtGui[0].it_td->u.td_wrapper_type

#define sipType_QPainter sipImportedTypes_qcamotorgui_QtGui[17].it_td
#define sipClass_QPainter sipImportedTypes_qcamotorgui_QtGui[17].it_td->u.td_wrapper_type

#define sipType_QPaintEngine sipImportedTypes_qcamotorgui_QtGui[15].it_td
#define sipClass_QPaintEngine sipImportedTypes_qcamotorgui_QtGui[15].it_td->u.td_wrapper_type
extern sipImportedTypeDef sipImportedTypes_qcamotorgui_QtGui[];

#define sipType_QWidget sipImportedTypes_qcamotorgui_QtWidgets[2].it_td
#define sipClass_QWidget sipImportedTypes_qcamotorgui_QtWidgets[2].it_td->u.td_wrapper_type

#define sipType_QPushButton sipImportedTypes_qcamotorgui_QtWidgets[1].it_td
#define sipClass_QPushButton sipImportedTypes_qcamotorgui_QtWidgets[1].it_td->u.td_wrapper_type

#define sipType_QDoubleSpinBox sipImportedTypes_qcamotorgui_QtWidgets[0].it_td
#define sipClass_QDoubleSpinBox sipImportedTypes_qcamotorgui_QtWidgets[0].it_td->u.td_wrapper_type
extern sipImportedTypeDef sipImportedTypes_qcamotorgui_QtWidgets[];

#define sipType_QCaMotor sipImportedTypes_qcamotorgui_qcamotor[0].it_td
#define sipClass_QCaMotor sipImportedTypes_qcamotorgui_qcamotor[0].it_td->u.td_wrapper_type
extern sipImportedTypeDef sipImportedTypes_qcamotorgui_qcamotor[];

typedef const QMetaObject *(*sip_qt_metaobject_func)(sipSimpleWrapper *,sipTypeDef *);
extern sip_qt_metaobject_func sip_qcamotorgui_qt_metaobject;

typedef int (*sip_qt_metacall_func)(sipSimpleWrapper *,sipTypeDef *,QMetaObject::Call,int,void **);
extern sip_qt_metacall_func sip_qcamotorgui_qt_metacall;

typedef bool (*sip_qt_metacast_func)(sipSimpleWrapper *, const sipTypeDef *, const char *, void **);
extern sip_qt_metacast_func sip_qcamotorgui_qt_metacast;

#endif
