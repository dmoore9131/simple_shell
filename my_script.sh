#!/bin/bash

################################################################################
# Set Configuration Variables
################################################################################
R=$RANDOM

TMP_DIR="/tmp"
COMMANDFILE="$TMP_DIR/my_script_command_$R"
STATUS="$TMP_DIR/my_script_status_$R"
OUTPUTFILE="$TMP_DIR/my_script_output_$R"
ERROR_OUTPUTFILE="$TMP_DIR/my_script_error_output_$R"
TMP_FILE="$TMP_DIR/my_script_tmp_$R"

################################################################################
# Most Used Commands, In Case the Environment is Missing
################################################################################
WHICH="/usr/bin/which"
SLEEP=`$WHICH sleep`
ECHO=`$WHICH echo`
CAT=`$WHICH cat`
GREP=`$WHICH grep`
WC=`$WHICH wc`
RM=`$WHICH rm`

################################################################################
# Command-Line Options and Parameters
################################################################################
usage=0

valgrind_error=0
ltrace=0

function usage()
{
	exitcode=$1

$ECHO "Usage: $0 shell test_file

Options:
--valgrind_error    Checks for valgrind errors
--ltrace            Checks for forbidden system/library calls
--help              Prints the help and exit"

	exit $exitcode
}

################################################################################
# Parse Command-Line Parameters
################################################################################
for arg in "$@"
do
	if [ "$arg" == "--valgrind_error" ]
	then
		let valgrind_error=1
		shift $ARGV
	elif [ "$arg" == "--ltrace" ]
	then
		let ltrace=1
		shift $ARGV
	elif [ "$arg" == "--help" ]
	then
		let usage=1
		shift $ARGV
	fi
done

[[ "$usage" -eq "1" ]] && usage 0
[[ "$#" -lt "2" ]] && usage 1

HSHELL=$1
TEST_FILE=$2

################################################################################
# Utility Functions
################################################################################
function stop_process()
{
	prog=$1
	base_shell=${prog##*/}

	running_shells=`$PIDOF "$base_shell" | $WC -l`
	if [ "$running_shells" -ne "0" ]
	then
		$KILLALL -9 "$base_shell" > /dev/null 2>&1
	fi
}

function cleanup()
{
	stop_process $HSHELL
	$RM -f $COMMANDFILE
	$RM -f $STATUS
	$RM -f $OUTPUTFILE
	$RM -f $ERROR_OUTPUTFILE
	$RM -f $TMP_FILE
}

################################################################################
# Start
################################################################################
stop_process $HSHELL
status=0

################################################################################
# Read and Execute Check Script
################################################################################
source $TEST_FILE

################################################################################
# Retrieve Shell Input (STDIN)
################################################################################
if [ -z ${shell_input+x} ]
then
	echo "The variable \$shell_input is not defined in $TEST_FILE!"
	exit 1
fi

################################################################################
# Preparing Command Script File
################################################################################
$ECHO -e -n "$ECHO " > $COMMANDFILE
$ECHO -e -n "\"$shell_input\"" >> $COMMANDFILE
$ECHO -e "\"$HSHELL\"" >> $COMMANDFILE
$CHMOD +x $COMMANDFILE

################################################################################
# Test Command Against Student Shell
################################################################################
. $COMMANDFILE

# Add your testing logic here...

################################################################################
# Cleanup and Quit
################################################################################
cleanup

[[ $status -eq 0 ]] && $ECHO -n "OK"
exit $status

