# setup chartmaster environment
#
# source this file from your ~/.bashrc
#
# relative to <kali>/bin/
CHARTMASTER=$(cd "$(dirname "$BASH_SOURCE")/.."; pwd)
CHARTMASTER_PYTHON=$(cd "$(dirname "$BASH_SOURCE")/../python"; pwd)
CHARTMASTER_LIB=$(cd "$(dirname "$BASH_SOURCE")/../lib"; pwd)

export CHARTMASTER
export PYTHONPATH="$CHARTMASTER_LIB:$PYTHONPATH"
export PYTHONPATH="$CHARTMASTER_PYTHON:$PYTHONPATH"
echo "notice: chartmaster tools have been set up."