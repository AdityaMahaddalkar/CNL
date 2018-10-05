set ns [ new Simulator ]

$ns color 1 Blue
$ns color 2 Red

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
set n3 [ $ns node ]
set n4 [ $ns node ]

$ns duplex-link $n0 $n1 2Mb 10ms DropTail
$ns duplex-link $n0 $n2 1.4Mb 15ms DropTail
$ns duplex-link $n0 $n3 1.7Mb 12ms DropTail
$ns duplex-link $n0 $n4 1.4Mb 20ms DropTail

$ns queue-limit $n0 $n2 10
$ns queue-limit $n0 $n4 13

$ns duplex-link-op $n0 $n1 orient up
$ns duplex-link-op $n0 $n2 orient left
$ns duplex-link-op $n0 $n3 orient down
$ns duplex-link-op $n0 $n4 orient right

$ns duplex-link-op $n0 $n2 queuePos 0.5
$ns duplex-link-op $n0 $n4 queuePos 0.5

#Setup TCP Agent
set tcp1 [ new Agent/TCP ]
$tcp1 set class_ 2
$ns attach-agent $n1 $tcp1
set sink1 [ new Agent/TCPSink ]
$ns attach-agent $n4 $sink1
$ns connect $tcp1 $sink1
$tcp1 set fid_ 1

# Setup UDP Agent
set udp [ new Agent/UDP ]
$ns attach-agent $n3 $udp
set null [ new Agent/Null ]
$ns attach-agent $n2 $null
$ns connect $udp $null
$udp set fid_ 2

# Setup FTP Agent
set ftp [ new Application/FTP ]
$ftp attach-agent $tcp1
$ftp set type_ FTP

# Setup CBR over UDP
set cbr [ new Application/Traffic/CBR ]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate_ 1.6mb
$cbr set random_ false

# Schedule events 
$ns at 0.2 "$cbr start"
$ns at 0.4 "$ftp start"
$ns at 3.4 "$cbr stop"
$ns at 3.6 "$ftp stop"
$ns at 4.0 "finish"

# run the simulation
$ns run




