#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
int
main(int argc, char** argv)
{
	ofstream outfile("cloud_filtered.txt", ios::out);

	// 将一个适当类型的输入文件加载到对象PointCloud中
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>());
	// 加载bun0.pcd文件，加载的文件在 PCL的测试数据中是存在的 
	pcl::io::loadPCDFile("mother_voxel_mlsUpsample.pcd", *cloud);
	std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height
		<< " data points (" << pcl::getFieldsList(*cloud) << ").\n";

	clock_t start = clock();

	float LeafSize = 0.15;
	// 创建滤波器对象
	pcl::VoxelGrid<pcl::PointXYZ> sor;
	sor.setInputCloud(cloud);
	sor.setLeafSize(LeafSize, LeafSize, LeafSize);
	sor.filter(*cloud_filtered);

	clock_t ends = clock();
	std::cerr << "Running Time : " << (double)(ends - start) / CLOCKS_PER_SEC << ".\n";

	outfile << "当包围盒设置为" << LeafSize << "时" << "： "; 

	outfile << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height
		<< " data points (" << pcl::getFieldsList(*cloud_filtered) << ").\n";

	std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height
		<< " data points (" << pcl::getFieldsList(*cloud_filtered) << ").\n";
	pcl::PCDWriter writer;
	pcl::io::savePCDFile("mother_voxel_mlsUpsample_voxel.pcd", *cloud_filtered);

	outfile.close();

	system("pause");
	return (0);
}
