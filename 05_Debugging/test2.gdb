set pagination off
set logging on

break range_get if I->number >= 28 && I->number <= 35
    command 1
    printf "@@@ %d %d %d %d\n", I->start, I->stop, I->step, I->current_elem
    continue
end

run -100 100 3 > /dev/null

set logging off
quit