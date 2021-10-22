set pagination off
set logging on

break range_get if I->current_elem % 5 == 0
    command 1
    printf "@@@ %d %d %d %d\n", I->start, I->stop, I->step, I->current_elem
    continue
end

run 1 12 > /dev/null

set logging off
quit