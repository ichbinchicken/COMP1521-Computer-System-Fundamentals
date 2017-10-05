echo "testing lru 5(pages) 4(frame)..."
./vmsim lru 5 4 < trace1 >out1
if diff out1 out-lru-5-4-trace1.txt
then
    echo "passed"
else
    exit
fi
echo 
echo "testing lru 8(pages) 4(frame)..."
./vmsim lru 8 4 < trace2 >out2
if diff out2 out-lru-8-4-trace2.txt
then
    echo "passed"
else
    exit
fi
echo 
echo "testing fifo 5(pages) 4(frame)..."
./vmsim fifo 5 4 < trace1 >out3
if diff out3 out-fifo-5-4-trace1.txt
then
    echo "passed"
else
    exit
fi
echo 
echo "testing fifo 8(pages) 4(frame)..."
./vmsim fifo 8 4 < trace2 >out4
if diff out4 out-fifo-8-4-trace2.txt
then
    echo "passed"
else
    exit
fi
echo 

rm out1 out2 out3 out4
