unset environment


define runwithinput
    run "$(cat ./args)" < ./input
end

define startwithinput
    tbreak main
    run "$(cat ./args)" < ./input
end
