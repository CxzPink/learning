#将命令行第一个参数赋值给变量path
path="$*"
#设置可执行文件路劲为bin，那么我们以后可以通过${bin} joint.vtk来调用程序。
bin="../bin/hex"
#判断path是否为空，为空打印信息并退出
if [ -z ${path} ]
then 
echo "empty path"
exit 
fi
#在屏幕上打印表头 name,n_hex,min_sj,ave_sj
echo "name,n_hex,min_sj,ave_sj"
#用ls命令获得文件名并赋值给变量files
files=$(ls $path)
#用for循环读取files中的每一个变量file
for file in $files
do
	#调用程序 | 筛选有用信息 | 打印需要的信息
    #$bin ____ | grep "INFO __" | echo $file,$(awk ____)
    $bin $path"/"$file | grep "INFO 38" | echo $file,$(awk '{printf "%d,%f,%f\n",$5,$7,$9}')
done