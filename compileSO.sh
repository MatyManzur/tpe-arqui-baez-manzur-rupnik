docker start arquiTPE
docker exec -it arquiTPE make clean
docker exec -it arquiTPE make -C /root/Toolchain
docker exec -it arquiTPE make -C /root/
docker stop arquiTPE
sudo ./run.sh $1
