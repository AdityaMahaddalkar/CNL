set ns [new Simulator]

$ns color 1 Blue

set nf [ open a.nam w ]
$ns namtrace-all $nf
set nf1 [ open b.tr w ]
$ns trace-all $nf1

proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam a.nam &
	exit 0
}

set n0 [ $ns node ]
set n1 [ $ns node ]
set n2 [ $ns node ]

$ns duplex-link $n0 $n1 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 1.5Mb 100ms DropTail

$ns queue-limit $n1 $n2 10

$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right

$ns duplex-link-op $n1 $n2 queuePos 0.5

set tcp1 [ new Agent/TCP ]
$tcp1 set class_ 2
$ns attach-agent $n0 $tcp1
set sink1 [ new Agent/TCPSink ]
$ns attach-agent $n2 $sink1
$ns connect $tcp1 $sink1
$tcp1 set fid_ 1

set ftp [ new Application/FTP ]
$ftp attach-agent $tcp1
$ftp set type_ FTP

$ns at 0.5 "$ftp start"
$ns at 4.5 "$ftp stop"
$ns at 5.0 "finish"

$ns run	
