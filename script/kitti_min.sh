# ========================
# kitti compile &run script
# ========================
echo
echo "============================================"
echo "##### => KITTI Dataset Evaluation <= #####"
echo "============================================"
mkdir -p ../build
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
./demo_main KITTI KITTI_config_min.txt
