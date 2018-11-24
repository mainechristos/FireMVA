#!/bin/bash
# reads signal input file and generates new file with BDT variable
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
export COIN_FULL_INDIRECT_RENDERING=1
echo $VO_CMS_SW_DIR
source $VO_CMS_SW_DIR/cmsset_default.sh
cd /cvmfs/cms-ib.cern.ch/nweek-02550/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_4_ROOT614_X_2018-11-11-0000/
export SCRAM_ARCH=slc6_amd64_gcc700
export DISPLAY=localhost:0.0
eval `scramv1 runtime -sh`
cd -
mkdir outFiles/Application_$1 
echo $2
mkdir outFiles/Application_$1/$2
cp Application_Fakes_2L_2017.C outFiles/Application_$1/$2/Application_Fakes_2L_2017.C
sed -i "s/QQQ/$2/g;" outFiles/Application_$1/$2/Application_Fakes_2L_2017.C
sed -i "s/JJJ/$1/g;" outFiles/Application_$1/$2/Application_Fakes_2L_2017.C
root -l -q outFiles/Application_$1/$2/Application_Fakes_2L_2017.C