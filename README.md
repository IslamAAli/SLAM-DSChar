# SLAM Datasets Characterization Framework
An extendable and generic SLAM dataset analysis and characterization framework suitable for characterizing visual-inertial SLAM datasets based on an extended number of characterization metrics. 

## Characterization Metrics
A characterization metric is a measurement of a certain quantity that can be used as a partial or a full descriptor of the SLAM dataset. In our system, we currently support general non-sensory metrics, inertial metrics, and visual metrics. The total number of supported metrics is currently at 73 different metrics. 

## Running the Framework
It is advised to run the docker version of the system in order to have a smooth operation. To do so, you need to first build the docker image:
```
./build_docker.sh
```
Then, you have to run the docker image, but change the path to mount the dataset you want to characterize.
```
./run_docker.sh
```
Make sure to update the path to your dataset inside:
```
in_data/you_ds_config_file.txt
```

## Credit / License 
This project is developed by Islam A. Ali, as part of my PhD thesis in Computing Science at the University of Alberta, Edmonton, Canada. For researchers/developers wishing to leverage or utilize the code, please use the citation of the paper below:

```
@inproceedings{ali2022we,
  title={Are We Ready for Robust and Resilient SLAM? A Framework For Quantitative Characterization of SLAM Datasets},
  author={Ali, Islam and Zhang, Hong},
  booktitle={2022 IEEE/RSJ International Conference on Intelligent Robots and Systems (IROS)},
  year={2022},
  pages={2810--2816},
  organization={IEEE}
}
```
The codebase is licensed under the GNU General Public License v3 (GPL-3) 

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)   
