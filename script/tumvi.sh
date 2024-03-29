# ========================
# kitti compile &run script
# ========================
echo
echo "============================================"
echo "##### => KITTI Dataset Evaluation <= #####"
echo "============================================"
cd ../build
rm demo_main
echo
echo "============================================"
echo "##### => Building ..              <= #####"
echo "============================================"
cmake ..
make
echo
echo "============================================"
echo "##### => Running ..               <= #####"
echo "============================================"
./demo_main TUM_VI TUM_VI_config.txt
