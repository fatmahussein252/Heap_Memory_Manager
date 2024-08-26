define allocatd
    set $x = 0
    while $x < 100
    if pointers[$x] != 0
        p pointers[$x]
    end
        set $x = $x + 1
    end
end


