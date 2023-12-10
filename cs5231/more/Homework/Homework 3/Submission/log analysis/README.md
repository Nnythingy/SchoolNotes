# Analysis of Audit Logs

The analysis script `analyse_log.py` is developed in Python3.

## Running the Analysis Script

1. Ensure the parsed log file is in the same directory as analyse_log.py.

2. Modify the variable `PARSED_LOG_FILE` to the name of the parsed log file. The default is `task1_parsed.log`.

3. Run the analysis script with:

```python
python3 analyse_log.py
```

```
Output:

219 /usr/include/linux/nl80211.h
80 /usr/include/linux/videodev2.h
73 /usr/include/linux/bpf.h
54 /usr/include/linux/pci_regs.h
48 /usr/include/linux/ethtool.h
45 /usr/include/linux/cec-funcs.h
45 /usr/include/linux/v4l2-controls.h
42 /usr/include/linux/cec.h
42 /usr/include/linux/sctp.h
42 /usr/include/linux/soundcard.h
```

![Analysis Output](analyse_log.png)
