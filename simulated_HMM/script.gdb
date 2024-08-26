
define freelst
    set $current = head
    while $current != 0
        p *$current
        set $current = $current->next
    end
end
