#!/bin/bash


FIELDS="DIR VELO ACCL BDST BVEL BACC MRES PREC EGU DHLM DLLM TWV ERES UEIP VMAX OFF RDBD ADEL"

printOneMotor() {

  if [ -z "$1" ] ; then
	return 0
  fi

  if caget $1 2>/dev/null >/dev/null ; then

    OUTSTRING="$(echo $1 | sed 's/:/, /1'),"
    OUTSTRING="$OUTSTRING \"$(caget -t $1.DESC 2>/dev/null)\","

    PVSTRD=""
    for fld in DIR VELO ACCL BDST BVEL BACC MRES PREC ; do
      PVSTRD="$PVSTRD ${1}.${fld}"
    done
    OUTSTRING="$OUTSTRING $(echo $(caget -nt $PVSTRD 2>/dev/null) | sed 's: :, :g' ),"

    OUTSTRING="$OUTSTRING \"$(caget -t $1.EGU 2>/dev/null)\","

    PVSTRD=""
    for fld in DHLM DLLM TWV ERES UEIP VMAX OFF RDBD ADEL ; do
      PVSTRD="$PVSTRD ${1}.${fld}"
    done
    OUTSTRING="$OUTSTRING $(echo $(caget -nt $PVSTRD 2>/dev/null) | sed 's: :, :g')"

    echo "$OUTSTRING"
    return $?

  else
    echo "Could not get information for motor \"$1\"." >&2
    return 1
  fi 

}



if [ -z "$1" ] ; then
  $0 $(AllMotorPVs.sh)
  exit $?
else
  echo "# P, M, DESC, DIR, VELO, ACCL, BDST, BVEL, BACC, MRES, PREC, EGU, DHLM, DLLM, TWV, ERES, UEIP, VMAX, OFF, RDBD, ADEL" 
  ret=0
  for mot in $@ ; do
    if ! printOneMotor $mot ; then
      ret=1
    fi
  done
  exit $ret
fi
 
