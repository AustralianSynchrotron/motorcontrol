/*
 * Internal module API header file.
 *
 * Generated by SIP 4.19.16
 */

#ifndef _pyqmotorstackAPI_H
#define _pyqmotorstackAPI_H

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
#define sipNameNr_mouseDoubleClickEvent 0
#define sipName_mouseDoubleClickEvent &sipStrings_pyqmotorstack[0]
#define sipNameNr_22 22
#define sipName_22 &sipStrings_pyqmotorstack[22]
#define sipNameNr_focusPreviousChild 42
#define sipName_focusPreviousChild &sipStrings_pyqmotorstack[42]
#define sipNameNr_focusNextPrevChild 61
#define sipName_focusNextPrevChild &sipStrings_pyqmotorstack[61]
#define sipNameNr_destroySubWindows 80
#define sipName_destroySubWindows &sipStrings_pyqmotorstack[80]
#define sipNameNr_hasHeightForWidth 98
#define sipName_hasHeightForWidth &sipStrings_pyqmotorstack[98]
#define sipNameNr_mouseReleaseEvent 116
#define sipName_mouseReleaseEvent &sipStrings_pyqmotorstack[116]
#define sipNameNr_loadConfiguration 134
#define sipName_loadConfiguration &sipStrings_pyqmotorstack[134]
#define sipNameNr_saveConfiguration 152
#define sipName_saveConfiguration &sipStrings_pyqmotorstack[152]
#define sipNameNr_isSignalConnected 170
#define sipName_isSignalConnected &sipStrings_pyqmotorstack[170]
#define sipNameNr_senderSignalIndex 188
#define sipName_senderSignalIndex &sipStrings_pyqmotorstack[188]
#define sipNameNr_206 206
#define sipName_206 &sipStrings_pyqmotorstack[206]
#define sipNameNr_destroyOldWindow 223
#define sipName_destroyOldWindow &sipStrings_pyqmotorstack[223]
#define sipNameNr_initializeWindow 240
#define sipName_initializeWindow &sipStrings_pyqmotorstack[240]
#define sipNameNr_updateMicroFocus 257
#define sipName_updateMicroFocus &sipStrings_pyqmotorstack[257]
#define sipNameNr_contextMenuEvent 274
#define sipName_contextMenuEvent &sipStrings_pyqmotorstack[274]
#define sipNameNr_inputMethodEvent 291
#define sipName_inputMethodEvent &sipStrings_pyqmotorstack[291]
#define sipNameNr_inputMethodQuery 308
#define sipName_inputMethodQuery &sipStrings_pyqmotorstack[308]
#define sipNameNr_disconnectNotify 325
#define sipName_disconnectNotify &sipStrings_pyqmotorstack[325]
#define sipNameNr_minimumSizeHint 342
#define sipName_minimumSizeHint &sipStrings_pyqmotorstack[342]
#define sipNameNr_mousePressEvent 358
#define sipName_mousePressEvent &sipStrings_pyqmotorstack[358]
#define sipNameNr_keyReleaseEvent 374
#define sipName_keyReleaseEvent &sipStrings_pyqmotorstack[374]
#define sipNameNr_focusNextChild 390
#define sipName_focusNextChild &sipStrings_pyqmotorstack[390]
#define sipNameNr_heightForWidth 405
#define sipName_heightForWidth &sipStrings_pyqmotorstack[405]
#define sipNameNr_dragLeaveEvent 420
#define sipName_dragLeaveEvent &sipStrings_pyqmotorstack[420]
#define sipNameNr_dragEnterEvent 435
#define sipName_dragEnterEvent &sipStrings_pyqmotorstack[435]
#define sipNameNr_mouseMoveEvent 450
#define sipName_mouseMoveEvent &sipStrings_pyqmotorstack[450]
#define sipNameNr_changedSignal 465
#define sipName_changedSignal &sipStrings_pyqmotorstack[465]
#define sipNameNr_sharedPainter 479
#define sipName_sharedPainter &sipStrings_pyqmotorstack[479]
#define sipNameNr_destroyWindow 493
#define sipName_destroyWindow &sipStrings_pyqmotorstack[493]
#define sipNameNr_thresholdTime 507
#define sipName_thresholdTime &sipStrings_pyqmotorstack[507]
#define sipNameNr_dragMoveEvent 521
#define sipName_dragMoveEvent &sipStrings_pyqmotorstack[521]
#define sipNameNr_keyPressEvent 535
#define sipName_keyPressEvent &sipStrings_pyqmotorstack[535]
#define sipNameNr_focusOutEvent 549
#define sipName_focusOutEvent &sipStrings_pyqmotorstack[549]
#define sipNameNr_connectNotify 328
#define sipName_connectNotify &sipStrings_pyqmotorstack[328]
#define sipNameNr_pyqmotorstack 563
#define sipName_pyqmotorstack &sipStrings_pyqmotorstack[563]
#define sipNameNr_focusInEvent 577
#define sipName_focusInEvent &sipStrings_pyqmotorstack[577]
#define sipNameNr_listChanged 590
#define sipName_listChanged &sipStrings_pyqmotorstack[590]
#define sipNameNr_removeMotor 602
#define sipName_removeMotor &sipStrings_pyqmotorstack[602]
#define sipNameNr_showGeneral 614
#define sipName_showGeneral &sipStrings_pyqmotorstack[614]
#define sipNameNr_QMotorStack 626
#define sipName_QMotorStack &sipStrings_pyqmotorstack[626]
#define sipNameNr_initPainter 638
#define sipName_initPainter &sipStrings_pyqmotorstack[638]
#define sipNameNr_nativeEvent 650
#define sipName_nativeEvent &sipStrings_pyqmotorstack[650]
#define sipNameNr_actionEvent 662
#define sipName_actionEvent &sipStrings_pyqmotorstack[662]
#define sipNameNr_changeEvent 674
#define sipName_changeEvent &sipStrings_pyqmotorstack[674]
#define sipNameNr_tabletEvent 686
#define sipName_tabletEvent &sipStrings_pyqmotorstack[686]
#define sipNameNr_resizeEvent 698
#define sipName_resizeEvent &sipStrings_pyqmotorstack[698]
#define sipNameNr_paintEngine 710
#define sipName_paintEngine &sipStrings_pyqmotorstack[710]
#define sipNameNr_customEvent 722
#define sipName_customEvent &sipStrings_pyqmotorstack[722]
#define sipNameNr_eventFilter 734
#define sipName_eventFilter &sipStrings_pyqmotorstack[734]
#define sipNameNr_enterEvent 746
#define sipName_enterEvent &sipStrings_pyqmotorstack[746]
#define sipNameNr_leaveEvent 757
#define sipName_leaveEvent &sipStrings_pyqmotorstack[757]
#define sipNameNr_constraint 768
#define sipName_constraint &sipStrings_pyqmotorstack[768]
#define sipNameNr_closeEvent 779
#define sipName_closeEvent &sipStrings_pyqmotorstack[779]
#define sipNameNr_repeatTime 790
#define sipName_repeatTime &sipStrings_pyqmotorstack[790]
#define sipNameNr_wheelEvent 801
#define sipName_wheelEvent &sipStrings_pyqmotorstack[801]
#define sipNameNr_columnSpan 812
#define sipName_columnSpan &sipStrings_pyqmotorstack[812]
#define sipNameNr_paintEvent 823
#define sipName_paintEvent &sipStrings_pyqmotorstack[823]
#define sipNameNr_setVisible 834
#define sipName_setVisible &sipStrings_pyqmotorstack[834]
#define sipNameNr_childEvent 845
#define sipName_childEvent &sipStrings_pyqmotorstack[845]
#define sipNameNr_timerEvent 856
#define sipName_timerEvent &sipStrings_pyqmotorstack[856]
#define sipNameNr_motorList 867
#define sipName_motorList &sipStrings_pyqmotorstack[867]
#define sipNameNr_dropEvent 877
#define sipName_dropEvent &sipStrings_pyqmotorstack[877]
#define sipNameNr_hideEvent 887
#define sipName_hideEvent &sipStrings_pyqmotorstack[887]
#define sipNameNr_showEvent 897
#define sipName_showEvent &sipStrings_pyqmotorstack[897]
#define sipNameNr_moveEvent 907
#define sipName_moveEvent &sipStrings_pyqmotorstack[907]
#define sipNameNr_alignment 917
#define sipName_alignment &sipStrings_pyqmotorstack[917]
#define sipNameNr_receivers 927
#define sipName_receivers &sipStrings_pyqmotorstack[927]
#define sipNameNr_addMotor 937
#define sipName_addMotor &sipStrings_pyqmotorstack[937]
#define sipNameNr_sizeHint 946
#define sipName_sizeHint &sipStrings_pyqmotorstack[946]
#define sipNameNr_property 955
#define sipName_property &sipStrings_pyqmotorstack[955]
#define sipNameNr_isLocked 964
#define sipName_isLocked &sipStrings_pyqmotorstack[964]
#define sipNameNr_rowSpan 973
#define sipName_rowSpan &sipStrings_pyqmotorstack[973]
#define sipNameNr_destroy 981
#define sipName_destroy &sipStrings_pyqmotorstack[981]
#define sipNameNr_devType 989
#define sipName_devType &sipStrings_pyqmotorstack[989]
#define sipNameNr_enabled 997
#define sipName_enabled &sipStrings_pyqmotorstack[997]
#define sipNameNr_metric 1005
#define sipName_metric &sipStrings_pyqmotorstack[1005]
#define sipNameNr_window 1012
#define sipName_window &sipStrings_pyqmotorstack[1012]
#define sipNameNr_create 1019
#define sipName_create &sipStrings_pyqmotorstack[1019]
#define sipNameNr_sender 1026
#define sipName_sender &sipStrings_pyqmotorstack[1026]
#define sipNameNr_system 1033
#define sipName_system &sipStrings_pyqmotorstack[1033]
#define sipNameNr_offset 1040
#define sipName_offset &sipStrings_pyqmotorstack[1040]
#define sipNameNr_column 1047
#define sipName_column &sipStrings_pyqmotorstack[1047]
#define sipNameNr_object 1054
#define sipName_object &sipStrings_pyqmotorstack[1054]
#define sipNameNr_clear 1061
#define sipName_clear &sipStrings_pyqmotorstack[1061]
#define sipNameNr_roles 1067
#define sipName_roles &sipStrings_pyqmotorstack[1067]
#define sipNameNr_event 1073
#define sipName_event &sipStrings_pyqmotorstack[1073]
#define sipNameNr_lock 1079
#define sipName_lock &sipStrings_pyqmotorstack[1079]
#define sipNameNr_mode 1084
#define sipName_mode &sipStrings_pyqmotorstack[1084]

#define sipMalloc                   sipAPI_pyqmotorstack->api_malloc
#define sipFree                     sipAPI_pyqmotorstack->api_free
#define sipBuildResult              sipAPI_pyqmotorstack->api_build_result
#define sipCallMethod               sipAPI_pyqmotorstack->api_call_method
#define sipCallProcedureMethod      sipAPI_pyqmotorstack->api_call_procedure_method
#define sipCallErrorHandler         sipAPI_pyqmotorstack->api_call_error_handler
#define sipParseResultEx            sipAPI_pyqmotorstack->api_parse_result_ex
#define sipParseResult              sipAPI_pyqmotorstack->api_parse_result
#define sipParseArgs                sipAPI_pyqmotorstack->api_parse_args
#define sipParseKwdArgs             sipAPI_pyqmotorstack->api_parse_kwd_args
#define sipParsePair                sipAPI_pyqmotorstack->api_parse_pair
#define sipInstanceDestroyed        sipAPI_pyqmotorstack->api_instance_destroyed
#define sipInstanceDestroyedEx      sipAPI_pyqmotorstack->api_instance_destroyed_ex
#define sipConvertFromSequenceIndex sipAPI_pyqmotorstack->api_convert_from_sequence_index
#define sipConvertFromSliceObject   sipAPI_pyqmotorstack->api_convert_from_slice_object
#define sipConvertFromVoidPtr       sipAPI_pyqmotorstack->api_convert_from_void_ptr
#define sipConvertToVoidPtr         sipAPI_pyqmotorstack->api_convert_to_void_ptr
#define sipAddException             sipAPI_pyqmotorstack->api_add_exception
#define sipNoFunction               sipAPI_pyqmotorstack->api_no_function
#define sipNoMethod                 sipAPI_pyqmotorstack->api_no_method
#define sipAbstractMethod           sipAPI_pyqmotorstack->api_abstract_method
#define sipBadClass                 sipAPI_pyqmotorstack->api_bad_class
#define sipBadCatcherResult         sipAPI_pyqmotorstack->api_bad_catcher_result
#define sipBadCallableArg           sipAPI_pyqmotorstack->api_bad_callable_arg
#define sipBadOperatorArg           sipAPI_pyqmotorstack->api_bad_operator_arg
#define sipTrace                    sipAPI_pyqmotorstack->api_trace
#define sipTransferBack             sipAPI_pyqmotorstack->api_transfer_back
#define sipTransferTo               sipAPI_pyqmotorstack->api_transfer_to
#define sipTransferBreak            sipAPI_pyqmotorstack->api_transfer_break
#define sipSimpleWrapper_Type       sipAPI_pyqmotorstack->api_simplewrapper_type
#define sipWrapper_Type             sipAPI_pyqmotorstack->api_wrapper_type
#define sipWrapperType_Type         sipAPI_pyqmotorstack->api_wrappertype_type
#define sipVoidPtr_Type             sipAPI_pyqmotorstack->api_voidptr_type
#define sipGetPyObject              sipAPI_pyqmotorstack->api_get_pyobject
#define sipGetAddress               sipAPI_pyqmotorstack->api_get_address
#define sipGetMixinAddress          sipAPI_pyqmotorstack->api_get_mixin_address
#define sipGetCppPtr                sipAPI_pyqmotorstack->api_get_cpp_ptr
#define sipGetComplexCppPtr         sipAPI_pyqmotorstack->api_get_complex_cpp_ptr
#define sipIsPyMethod               sipAPI_pyqmotorstack->api_is_py_method
#define sipCallHook                 sipAPI_pyqmotorstack->api_call_hook
#define sipEndThread                sipAPI_pyqmotorstack->api_end_thread
#define sipConnectRx                sipAPI_pyqmotorstack->api_connect_rx
#define sipDisconnectRx             sipAPI_pyqmotorstack->api_disconnect_rx
#define sipRaiseUnknownException    sipAPI_pyqmotorstack->api_raise_unknown_exception
#define sipRaiseTypeException       sipAPI_pyqmotorstack->api_raise_type_exception
#define sipBadLengthForSlice        sipAPI_pyqmotorstack->api_bad_length_for_slice
#define sipAddTypeInstance          sipAPI_pyqmotorstack->api_add_type_instance
#define sipFreeSipslot              sipAPI_pyqmotorstack->api_free_sipslot
#define sipSameSlot                 sipAPI_pyqmotorstack->api_same_slot
#define sipPySlotExtend             sipAPI_pyqmotorstack->api_pyslot_extend
#define sipConvertRx                sipAPI_pyqmotorstack->api_convert_rx
#define sipAddDelayedDtor           sipAPI_pyqmotorstack->api_add_delayed_dtor
#define sipCanConvertToType         sipAPI_pyqmotorstack->api_can_convert_to_type
#define sipConvertToType            sipAPI_pyqmotorstack->api_convert_to_type
#define sipForceConvertToType       sipAPI_pyqmotorstack->api_force_convert_to_type
#define sipCanConvertToEnum         sipAPI_pyqmotorstack->api_can_convert_to_enum
#define sipConvertToEnum            sipAPI_pyqmotorstack->api_convert_to_enum
#define sipConvertToBool            sipAPI_pyqmotorstack->api_convert_to_bool
#define sipReleaseType              sipAPI_pyqmotorstack->api_release_type
#define sipConvertFromType          sipAPI_pyqmotorstack->api_convert_from_type
#define sipConvertFromNewType       sipAPI_pyqmotorstack->api_convert_from_new_type
#define sipConvertFromNewPyType     sipAPI_pyqmotorstack->api_convert_from_new_pytype
#define sipConvertFromEnum          sipAPI_pyqmotorstack->api_convert_from_enum
#define sipGetState                 sipAPI_pyqmotorstack->api_get_state
#define sipExportSymbol             sipAPI_pyqmotorstack->api_export_symbol
#define sipImportSymbol             sipAPI_pyqmotorstack->api_import_symbol
#define sipFindType                 sipAPI_pyqmotorstack->api_find_type
#define sipFindNamedEnum            sipAPI_pyqmotorstack->api_find_named_enum
#define sipBytes_AsChar             sipAPI_pyqmotorstack->api_bytes_as_char
#define sipBytes_AsString           sipAPI_pyqmotorstack->api_bytes_as_string
#define sipString_AsASCIIChar       sipAPI_pyqmotorstack->api_string_as_ascii_char
#define sipString_AsASCIIString     sipAPI_pyqmotorstack->api_string_as_ascii_string
#define sipString_AsLatin1Char      sipAPI_pyqmotorstack->api_string_as_latin1_char
#define sipString_AsLatin1String    sipAPI_pyqmotorstack->api_string_as_latin1_string
#define sipString_AsUTF8Char        sipAPI_pyqmotorstack->api_string_as_utf8_char
#define sipString_AsUTF8String      sipAPI_pyqmotorstack->api_string_as_utf8_string
#define sipUnicode_AsWChar          sipAPI_pyqmotorstack->api_unicode_as_wchar
#define sipUnicode_AsWString        sipAPI_pyqmotorstack->api_unicode_as_wstring
#define sipConvertFromConstVoidPtr  sipAPI_pyqmotorstack->api_convert_from_const_void_ptr
#define sipConvertFromVoidPtrAndSize    sipAPI_pyqmotorstack->api_convert_from_void_ptr_and_size
#define sipConvertFromConstVoidPtrAndSize   sipAPI_pyqmotorstack->api_convert_from_const_void_ptr_and_size
#define sipInvokeSlot               sipAPI_pyqmotorstack->api_invoke_slot
#define sipInvokeSlotEx             sipAPI_pyqmotorstack->api_invoke_slot_ex
#define sipSaveSlot                 sipAPI_pyqmotorstack->api_save_slot
#define sipClearAnySlotReference    sipAPI_pyqmotorstack->api_clear_any_slot_reference
#define sipVisitSlot                sipAPI_pyqmotorstack->api_visit_slot
#define sipWrappedTypeName(wt)      ((wt)->wt_td->td_cname)
#define sipDeprecated               sipAPI_pyqmotorstack->api_deprecated
#define sipGetReference             sipAPI_pyqmotorstack->api_get_reference
#define sipKeepReference            sipAPI_pyqmotorstack->api_keep_reference
#define sipRegisterProxyResolver    sipAPI_pyqmotorstack->api_register_proxy_resolver
#define sipRegisterPyType           sipAPI_pyqmotorstack->api_register_py_type
#define sipTypeFromPyTypeObject     sipAPI_pyqmotorstack->api_type_from_py_type_object
#define sipTypeScope                sipAPI_pyqmotorstack->api_type_scope
#define sipResolveTypedef           sipAPI_pyqmotorstack->api_resolve_typedef
#define sipRegisterAttributeGetter  sipAPI_pyqmotorstack->api_register_attribute_getter
#define sipIsAPIEnabled             sipAPI_pyqmotorstack->api_is_api_enabled
#define sipSetDestroyOnExit         sipAPI_pyqmotorstack->api_set_destroy_on_exit
#define sipEnableAutoconversion     sipAPI_pyqmotorstack->api_enable_autoconversion
#define sipEnableOverflowChecking   sipAPI_pyqmotorstack->api_enable_overflow_checking
#define sipInitMixin                sipAPI_pyqmotorstack->api_init_mixin
#define sipExportModule             sipAPI_pyqmotorstack->api_export_module
#define sipInitModule               sipAPI_pyqmotorstack->api_init_module
#define sipGetInterpreter           sipAPI_pyqmotorstack->api_get_interpreter
#define sipSetNewUserTypeHandler    sipAPI_pyqmotorstack->api_set_new_user_type_handler
#define sipSetTypeUserData          sipAPI_pyqmotorstack->api_set_type_user_data
#define sipGetTypeUserData          sipAPI_pyqmotorstack->api_get_type_user_data
#define sipPyTypeDict               sipAPI_pyqmotorstack->api_py_type_dict
#define sipPyTypeName               sipAPI_pyqmotorstack->api_py_type_name
#define sipGetCFunction             sipAPI_pyqmotorstack->api_get_c_function
#define sipGetMethod                sipAPI_pyqmotorstack->api_get_method
#define sipFromMethod               sipAPI_pyqmotorstack->api_from_method
#define sipGetDate                  sipAPI_pyqmotorstack->api_get_date
#define sipFromDate                 sipAPI_pyqmotorstack->api_from_date
#define sipGetDateTime              sipAPI_pyqmotorstack->api_get_datetime
#define sipFromDateTime             sipAPI_pyqmotorstack->api_from_datetime
#define sipGetTime                  sipAPI_pyqmotorstack->api_get_time
#define sipFromTime                 sipAPI_pyqmotorstack->api_from_time
#define sipIsUserType               sipAPI_pyqmotorstack->api_is_user_type
#define sipGetFrame                 sipAPI_pyqmotorstack->api_get_frame
#define sipCheckPluginForType       sipAPI_pyqmotorstack->api_check_plugin_for_type
#define sipUnicodeNew               sipAPI_pyqmotorstack->api_unicode_new
#define sipUnicodeWrite             sipAPI_pyqmotorstack->api_unicode_write
#define sipUnicodeData              sipAPI_pyqmotorstack->api_unicode_data
#define sipGetBufferInfo            sipAPI_pyqmotorstack->api_get_buffer_info
#define sipReleaseBufferInfo        sipAPI_pyqmotorstack->api_release_buffer_info
#define sipIsOwnedByPython          sipAPI_pyqmotorstack->api_is_owned_by_python
#define sipIsDerivedClass           sipAPI_pyqmotorstack->api_is_derived_class
#define sipGetUserObject            sipAPI_pyqmotorstack->api_get_user_object
#define sipSetUserObject            sipAPI_pyqmotorstack->api_set_user_object
#define sipRegisterEventHandler     sipAPI_pyqmotorstack->api_register_event_handler
#define sipLong_AsChar              sipAPI_pyqmotorstack->api_long_as_char
#define sipLong_AsSignedChar        sipAPI_pyqmotorstack->api_long_as_signed_char
#define sipLong_AsUnsignedChar      sipAPI_pyqmotorstack->api_long_as_unsigned_char
#define sipLong_AsShort             sipAPI_pyqmotorstack->api_long_as_short
#define sipLong_AsUnsignedShort     sipAPI_pyqmotorstack->api_long_as_unsigned_short
#define sipLong_AsInt               sipAPI_pyqmotorstack->api_long_as_int
#define sipLong_AsUnsignedInt       sipAPI_pyqmotorstack->api_long_as_unsigned_int
#define sipLong_AsLong              sipAPI_pyqmotorstack->api_long_as_long
#define sipLong_AsUnsignedLong      sipAPI_pyqmotorstack->api_long_as_unsigned_long
#define sipLong_AsLongLong          sipAPI_pyqmotorstack->api_long_as_long_long
#define sipLong_AsUnsignedLongLong  sipAPI_pyqmotorstack->api_long_as_unsigned_long_long
#define sipLong_AsSizeT             sipAPI_pyqmotorstack->api_long_as_size_t

/* These are deprecated. */
#define sipMapStringToClass         sipAPI_pyqmotorstack->api_map_string_to_class
#define sipMapIntToClass            sipAPI_pyqmotorstack->api_map_int_to_class
#define sipFindClass                sipAPI_pyqmotorstack->api_find_class
#define sipFindMappedType           sipAPI_pyqmotorstack->api_find_mapped_type
#define sipConvertToArray           sipAPI_pyqmotorstack->api_convert_to_array
#define sipConvertToTypedArray      sipAPI_pyqmotorstack->api_convert_to_typed_array
#define sipEnableGC                 sipAPI_pyqmotorstack->api_enable_gc
#define sipPrintObject              sipAPI_pyqmotorstack->api_print_object
#define sipWrapper_Check(w)         PyObject_TypeCheck((w), sipAPI_pyqmotorstack->api_wrapper_type)
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
extern const char sipStrings_pyqmotorstack[];

#define sipType_QMotorStack sipExportedTypes_pyqmotorstack[2]
#define sipClass_QMotorStack sipExportedTypes_pyqmotorstack[2]->u.td_wrapper_type

extern sipClassTypeDef sipTypeDef_pyqmotorstack_QMotorStack;

#define sipType_QList_0101QCaMotor sipExportedTypes_pyqmotorstack[0]

extern sipMappedTypeDef sipTypeDef_pyqmotorstack_QList_0101QCaMotor;

#define sipType_QList_0101QCaMotorGUI sipExportedTypes_pyqmotorstack[1]

extern sipMappedTypeDef sipTypeDef_pyqmotorstack_QList_0101QCaMotorGUI;

/* The SIP API, this module's API and the APIs of any imported modules. */
extern const sipAPIDef *sipAPI_pyqmotorstack;
extern sipExportedModuleDef sipModuleAPI_pyqmotorstack;
extern sipTypeDef *sipExportedTypes_pyqmotorstack[];

#define sipType_Qt_InputMethodQuery sipImportedTypes_pyqmotorstack_QtCore[10].it_td
#define sipEnum_Qt_InputMethodQuery sipImportedTypes_pyqmotorstack_QtCore[10].it_td->u.td_py_type

#define sipType_QObject sipImportedTypes_pyqmotorstack_QtCore[4].it_td
#define sipClass_QObject sipImportedTypes_pyqmotorstack_QtCore[4].it_td->u.td_wrapper_type

#define sipType_QByteArray sipImportedTypes_pyqmotorstack_QtCore[0].it_td
#define sipClass_QByteArray sipImportedTypes_pyqmotorstack_QtCore[0].it_td->u.td_wrapper_type

#define sipType_QEvent sipImportedTypes_pyqmotorstack_QtCore[2].it_td
#define sipClass_QEvent sipImportedTypes_pyqmotorstack_QtCore[2].it_td->u.td_wrapper_type

#define sipType_QTimerEvent sipImportedTypes_pyqmotorstack_QtCore[8].it_td
#define sipClass_QTimerEvent sipImportedTypes_pyqmotorstack_QtCore[8].it_td->u.td_wrapper_type

#define sipType_QChildEvent sipImportedTypes_pyqmotorstack_QtCore[1].it_td
#define sipClass_QChildEvent sipImportedTypes_pyqmotorstack_QtCore[1].it_td->u.td_wrapper_type

#define sipType_QMetaMethod sipImportedTypes_pyqmotorstack_QtCore[3].it_td
#define sipClass_QMetaMethod sipImportedTypes_pyqmotorstack_QtCore[3].it_td->u.td_wrapper_type

#define sipType_QSize sipImportedTypes_pyqmotorstack_QtCore[5].it_td
#define sipClass_QSize sipImportedTypes_pyqmotorstack_QtCore[5].it_td->u.td_wrapper_type

#define sipType_QVariant sipImportedTypes_pyqmotorstack_QtCore[9].it_td
#define sipClass_QVariant sipImportedTypes_pyqmotorstack_QtCore[9].it_td->u.td_wrapper_type

#define sipType_QStringList sipImportedTypes_pyqmotorstack_QtCore[7].it_td

#define sipType_QString sipImportedTypes_pyqmotorstack_QtCore[6].it_td

#define sipType_quintptr sipImportedTypes_pyqmotorstack_QtCore[11].it_td
extern sipImportedTypeDef sipImportedTypes_pyqmotorstack_QtCore[];
extern sipImportedVirtErrorHandlerDef sipImportedVirtErrorHandlers_pyqmotorstack_QtCore[];

#define sipType_QPaintDevice sipImportedTypes_pyqmotorstack_QtGui[13].it_td
#define sipClass_QPaintDevice sipImportedTypes_pyqmotorstack_QtGui[13].it_td->u.td_wrapper_type

#define sipType_QPaintDevice_PaintDeviceMetric sipImportedTypes_pyqmotorstack_QtGui[14].it_td
#define sipEnum_QPaintDevice_PaintDeviceMetric sipImportedTypes_pyqmotorstack_QtGui[14].it_td->u.td_py_type

#define sipType_QMouseEvent sipImportedTypes_pyqmotorstack_QtGui[11].it_td
#define sipClass_QMouseEvent sipImportedTypes_pyqmotorstack_QtGui[11].it_td->u.td_wrapper_type

#define sipType_QWheelEvent sipImportedTypes_pyqmotorstack_QtGui[21].it_td
#define sipClass_QWheelEvent sipImportedTypes_pyqmotorstack_QtGui[21].it_td->u.td_wrapper_type

#define sipType_QTabletEvent sipImportedTypes_pyqmotorstack_QtGui[20].it_td
#define sipClass_QTabletEvent sipImportedTypes_pyqmotorstack_QtGui[20].it_td->u.td_wrapper_type

#define sipType_QKeyEvent sipImportedTypes_pyqmotorstack_QtGui[10].it_td
#define sipClass_QKeyEvent sipImportedTypes_pyqmotorstack_QtGui[10].it_td->u.td_wrapper_type

#define sipType_QFocusEvent sipImportedTypes_pyqmotorstack_QtGui[7].it_td
#define sipClass_QFocusEvent sipImportedTypes_pyqmotorstack_QtGui[7].it_td->u.td_wrapper_type

#define sipType_QPaintEvent sipImportedTypes_pyqmotorstack_QtGui[16].it_td
#define sipClass_QPaintEvent sipImportedTypes_pyqmotorstack_QtGui[16].it_td->u.td_wrapper_type

#define sipType_QMoveEvent sipImportedTypes_pyqmotorstack_QtGui[12].it_td
#define sipClass_QMoveEvent sipImportedTypes_pyqmotorstack_QtGui[12].it_td->u.td_wrapper_type

#define sipType_QResizeEvent sipImportedTypes_pyqmotorstack_QtGui[18].it_td
#define sipClass_QResizeEvent sipImportedTypes_pyqmotorstack_QtGui[18].it_td->u.td_wrapper_type

#define sipType_QCloseEvent sipImportedTypes_pyqmotorstack_QtGui[1].it_td
#define sipClass_QCloseEvent sipImportedTypes_pyqmotorstack_QtGui[1].it_td->u.td_wrapper_type

#define sipType_QShowEvent sipImportedTypes_pyqmotorstack_QtGui[19].it_td
#define sipClass_QShowEvent sipImportedTypes_pyqmotorstack_QtGui[19].it_td->u.td_wrapper_type

#define sipType_QHideEvent sipImportedTypes_pyqmotorstack_QtGui[8].it_td
#define sipClass_QHideEvent sipImportedTypes_pyqmotorstack_QtGui[8].it_td->u.td_wrapper_type

#define sipType_QContextMenuEvent sipImportedTypes_pyqmotorstack_QtGui[2].it_td
#define sipClass_QContextMenuEvent sipImportedTypes_pyqmotorstack_QtGui[2].it_td->u.td_wrapper_type

#define sipType_QInputMethodEvent sipImportedTypes_pyqmotorstack_QtGui[9].it_td
#define sipClass_QInputMethodEvent sipImportedTypes_pyqmotorstack_QtGui[9].it_td->u.td_wrapper_type

#define sipType_QDropEvent sipImportedTypes_pyqmotorstack_QtGui[6].it_td
#define sipClass_QDropEvent sipImportedTypes_pyqmotorstack_QtGui[6].it_td->u.td_wrapper_type

#define sipType_QDragMoveEvent sipImportedTypes_pyqmotorstack_QtGui[5].it_td
#define sipClass_QDragMoveEvent sipImportedTypes_pyqmotorstack_QtGui[5].it_td->u.td_wrapper_type

#define sipType_QDragEnterEvent sipImportedTypes_pyqmotorstack_QtGui[3].it_td
#define sipClass_QDragEnterEvent sipImportedTypes_pyqmotorstack_QtGui[3].it_td->u.td_wrapper_type

#define sipType_QDragLeaveEvent sipImportedTypes_pyqmotorstack_QtGui[4].it_td
#define sipClass_QDragLeaveEvent sipImportedTypes_pyqmotorstack_QtGui[4].it_td->u.td_wrapper_type

#define sipType_QActionEvent sipImportedTypes_pyqmotorstack_QtGui[0].it_td
#define sipClass_QActionEvent sipImportedTypes_pyqmotorstack_QtGui[0].it_td->u.td_wrapper_type

#define sipType_QPainter sipImportedTypes_pyqmotorstack_QtGui[17].it_td
#define sipClass_QPainter sipImportedTypes_pyqmotorstack_QtGui[17].it_td->u.td_wrapper_type

#define sipType_QPaintEngine sipImportedTypes_pyqmotorstack_QtGui[15].it_td
#define sipClass_QPaintEngine sipImportedTypes_pyqmotorstack_QtGui[15].it_td->u.td_wrapper_type
extern sipImportedTypeDef sipImportedTypes_pyqmotorstack_QtGui[];

#define sipType_QWidget sipImportedTypes_pyqmotorstack_QtWidgets[0].it_td
#define sipClass_QWidget sipImportedTypes_pyqmotorstack_QtWidgets[0].it_td->u.td_wrapper_type
extern sipImportedTypeDef sipImportedTypes_pyqmotorstack_QtWidgets[];

#define sipType_QCaMotor sipImportedTypes_pyqmotorstack_pyqcamotor[0].it_td
#define sipClass_QCaMotor sipImportedTypes_pyqmotorstack_pyqcamotor[0].it_td->u.td_wrapper_type
extern sipImportedTypeDef sipImportedTypes_pyqmotorstack_pyqcamotor[];

#define sipType_QCaMotorGUI sipImportedTypes_pyqmotorstack_pyqcamotorgui[0].it_td
#define sipClass_QCaMotorGUI sipImportedTypes_pyqmotorstack_pyqcamotorgui[0].it_td->u.td_wrapper_type
extern sipImportedTypeDef sipImportedTypes_pyqmotorstack_pyqcamotorgui[];

typedef const QMetaObject *(*sip_qt_metaobject_func)(sipSimpleWrapper *,sipTypeDef *);
extern sip_qt_metaobject_func sip_pyqmotorstack_qt_metaobject;

typedef int (*sip_qt_metacall_func)(sipSimpleWrapper *,sipTypeDef *,QMetaObject::Call,int,void **);
extern sip_qt_metacall_func sip_pyqmotorstack_qt_metacall;

typedef bool (*sip_qt_metacast_func)(sipSimpleWrapper *, const sipTypeDef *, const char *, void **);
extern sip_qt_metacast_func sip_pyqmotorstack_qt_metacast;

#endif
