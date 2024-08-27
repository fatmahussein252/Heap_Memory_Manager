
define freelst
    set $current = head
    while $current != mybrk
        p *$current
        set $current = $current->next
    end
    p mybrk
end
