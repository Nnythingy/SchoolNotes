package Operations;

import CustomExceptions.DuplicateException;
import CustomExceptions.OfficeShareException;
import CustomExceptions.TimeClashException;
import Enums.ExceptionType;
import Enums.Priority;
import Enums.RecurrenceScheduleType;
import Enums.TimeUnit;
import Model_Classes.*;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.Date;

public class TaskCreator {
    private static final String UPDATED_DESCRIPTION_ERROR = "There is a formatting error in your updated description";
    private static final String DURATION_FORMAT_ERROR = "There's a problem with the duration you've specified, default to no duration";
    private static final String RECURRENCE_FORMAT_ERROR = "There seems to some mistake in your recurrence entry, "
            +"will be setting recurrence as none";
    private static final String STARTING_DATE_FORMAT_ERROR = "Wrong date format, starting date is set default to current date";
    private static final String ENDING_DATE_FORMAT_ERROR = "Wrong date format, ending date is set default to current date";
    public static final String PRIORITY_WILL_BE_SET_AS_LOW = "There seems to some mistake in your priority entry,"
            + " will be setting priority as low";
    private Parser parser;

    /**
     * Empty constructor for a TaskCreator.
     */
    public TaskCreator() {
        parser = new Parser();
    }

    /**
     * Check if a character in a String is a flag
     * @param c the character to be checked
     * @return
     */
    public boolean isFlag(char c) {
        return  c == '#' ||
                c == '(' ||
                c == '*' ||
                c == '&' ||
                c == '@' ||
                c == '^' ||
                c == '!' ||
                c == '%' ||
                c == '-';
    }

    /**
     * Find the first flag of a given input String
     * @param input
     * @return
     */
    public String findFirstFlag(String input) {
        char[] var = input.toCharArray();
        Character firstFlag = null;
        for (Character c: var) {
            if (isFlag(c)) {
                firstFlag = c;
                break;
            }
        }
        if (firstFlag == null) return null;
        return firstFlag.toString();
    }

    /**
     * Extract a field with the given input and the flag corresponding to such field
     * @param input
     * @param flag
     * @return
     */
    public String extractField(String input, String flag) {
        String[] fieldArray = input.split("\\" + flag);

        if (fieldArray.length <= 1)
            return null;

        String nextFlag = "\\" + findFirstFlag(fieldArray[1]);
        if (nextFlag == null) return fieldArray[1].trim();
        return fieldArray[1].split(nextFlag)[0].trim();
    }

    /**
     * Extract the task type from the user's input.
     * @param input user's input
     * @return the task type
     * @throws OfficeShareException when the task type is invalid
     */
    public String extractType(String input) throws OfficeShareException {
        String type = extractField(input,"#");
        if (type == null)
            throw new OfficeShareException(ExceptionType.emptyTaskType);
        return type.trim();
    }

    /**
     * Extract the description of a task from user's input.
     * @param input user's input
     * @return the description of the task
     * @throws OfficeShareException when there's no description detected
     */
    public String extractDescription(String input) throws OfficeShareException {
        String description = extractField(input,"-");
        if (description == null)
            throw new OfficeShareException(ExceptionType.emptyDescription);
        return description;
    }

    /**
     * Extract the priority of a task from user's input.
     * @param input user's input
     * @return the priority of the task
     */
    public Priority extractPriority(String input) throws OfficeShareException {
        Priority priority;
        String inputPriority = extractField(input,"*");
        if (inputPriority != null) {
            try {
                priority = Priority.valueOf(inputPriority);
            } catch (IllegalArgumentException e) {
                System.out.println(PRIORITY_WILL_BE_SET_AS_LOW);
                priority = Priority.low;
            }
        } else {
            priority = Priority.low;
        }
        return priority;
    }

    /**
     * Extract the date and time of a task from user's input.
     * @param input user's input
     * @return the date and time of the task
     * @throws OfficeShareException when there is no date and time detected or the format of date and time is invalid
     */
    public ArrayList<Date> extractDate(String input) throws OfficeShareException {
        // counts the number of '&' tags to determine if the user input a single date or double dates
        int count = 0;
        char[] inputAsChar = input.toCharArray();
        for (char c: inputAsChar) {
            if (c == '&') {
                count++;
            }
        }

        ArrayList<Date> dates = new ArrayList<>();
        Date currentDate = new Date();
        if (count > 0) {
            if (count == 1) {
                try {
                    String dateInput = extractField(input,"&");
                    Date date;
                    date = parser.formatDate(dateInput);
                    if (date.before(currentDate)) {
                        // the input date is before the current date
                        throw new OfficeShareException(ExceptionType.invalidDateError);
                    }
                    dates.add(date);
                } catch (ArrayIndexOutOfBoundsException a) {
                    throw new OfficeShareException(ExceptionType.emptyDate);
                }
            } else {
                String fromInput = extractField(input,"&");
                String toInput = extractField(input.substring(input.lastIndexOf(fromInput)),"&");
                Date from = new Date();
                Date to = new Date();

                try {
                    from = parser.formatDate(fromInput);
                    dates.add(from);
                } catch (OfficeShareException e) {
                    System.out.println(STARTING_DATE_FORMAT_ERROR);
                    dates.add(currentDate);
                }
                try {
                    to = parser.formatDate(toInput);
                    dates.add(to);
                } catch (OfficeShareException e) {
                    System.out.println(ENDING_DATE_FORMAT_ERROR);
                }
                if (from.before(currentDate)) {
                    // input date is before the current date
                    throw new OfficeShareException(ExceptionType.invalidDateError);
                }
                if (to.before(from)) {
                    // the date is before the current date or is before the starting
                    // date of the leave
                    throw new OfficeShareException(ExceptionType.invalidDateRange);
                }
            }
        } else {
            throw new OfficeShareException(ExceptionType.emptyDate);
        }
        return dates;
    }

    /**
     * Extract the assignee of a task from user's input.
     * @param input user's input
     * @return the name of the assignee
     */
    public String extractAssignee(String input) throws OfficeShareException {
        String assignee = extractField(input,"@");
        if (assignee == null)
            assignee = "everyone";
        return assignee;
    }

    /**
     * Extract the recurrence schedule of task from user's input.
     * @param input user's input
     * @return the recurrence schedule of the task
     */
    public RecurrenceScheduleType extractRecurrence(String input) throws OfficeShareException {
        RecurrenceScheduleType recurrence;
        String inputRecurrence = extractField(input,"%");
        if (inputRecurrence != null) {
            try {
                recurrence = RecurrenceScheduleType.valueOf(inputRecurrence);
            } catch (IllegalArgumentException | IndexOutOfBoundsException e) {
                System.out.println(RECURRENCE_FORMAT_ERROR);
                recurrence = RecurrenceScheduleType.none;
            }
        } else {
            recurrence = RecurrenceScheduleType.none;
        }

        return  recurrence;
    }

    /**
     * Extract the duration of a task from user's input.
     * @param input user's input
     * @return the amount of time and unit of the duration as a Pair of Integer and TimeUnit
     */
    public Pair<Integer, TimeUnit> extractDuration(String input) throws OfficeShareException {
        int duration;
        TimeUnit unit;
        String inputDuration = extractField(input,"^");
        if (inputDuration != null) {
            try {
                String[] var = inputDuration.split(" ");
                duration = Integer.parseInt(var[0].trim());
                unit = TimeUnit.valueOf(var[1].trim());
            } catch (IllegalArgumentException | ArrayIndexOutOfBoundsException e) {
                System.out.println(DURATION_FORMAT_ERROR);
                duration = 0;
                unit = TimeUnit.unDefined;
            }
        } else {
            duration = 0;
            unit = TimeUnit.unDefined;
        }

        if (duration < 0) {
            throw new OfficeShareException(ExceptionType.negativeTimeAmount);
        }
        return new Pair<>(duration,unit);
    }

    /**
     * Checks if input string has special flags used in the input format.
     * @param input input to be checked
     * @return a boolean value denoting if the input contains such flags
     */
    private boolean hasSpecialCharacters(String input) {
        boolean isInvalid = false;
        if (input.contains("#")) {
            isInvalid = true;
        } else if (input.contains("@")) {
            isInvalid = true;
        } else if (input.contains("!")) {
            isInvalid = true;
        } else if (input.contains("*")) {
            isInvalid = true;
        } else if (input.contains("^")) {
            isInvalid = true;
        } else if (input.contains("%")) {
            isInvalid = true;
        } else if (input.contains("&")) {
            isInvalid = true;
        } else if (input.contains("(")) {
            isInvalid = true;
        }
        return isInvalid;
    }

    /**
     * Extract the reminder flag of a task from user's input.
     * @param input user's input
     * @return the reminder flag of the task
     */
    public boolean extractReminder(String input) {
        String reminder = extractField(input, "!");
        if (reminder != null) {
            return reminder.contains("R");
        } else {
            return false;
        }
    }

    /**
     * Create a new task based on the description the user key in.
     * @param input the description of the task
     * @return a new Task object created based on the description
     * @throws OfficeShareException when there are some formatting errors
     */
    public Task create(String input) throws OfficeShareException, DuplicateException, TimeClashException {
        // extract the Task Type
        String type = this.extractType(input);

        // extract the priority
        Priority priority = this.extractPriority(input);

        // extract the description
        String description = this.extractDescription(input);

        // check for duplicates and time clashes
        int duplicateCheck;
        int timeClashCheck;

        // extract date
        ArrayList<Date> dates = this.extractDate(input);
        Date date = new Date();
        Date from = new Date();
        Date to = new Date();

        if (dates.size() == 1) {
            date = dates.get(0);
        } else {
            from = dates.get(0);
            to = dates.get(1);
        }

        // extract the assignee
        String assignee = this.extractAssignee(input);

        // extract recurrence schedule
        RecurrenceScheduleType recurrence = this.extractRecurrence(input);

        //extract duration
        Pair<Integer, TimeUnit> durationAndUnit = this.extractDuration(input);
        int duration = durationAndUnit.getKey();

        TimeUnit unit = durationAndUnit.getValue();

        //extract reminder
        boolean remind = this.extractReminder(input);

        if (type.equals("assignment") || type.equals("as")) {
            Assignment assignment = new Assignment(description, date);
            assignment.setPriority(priority);
            assignment.setAssignee(assignee);
            assignment.setRecurrenceSchedule(recurrence);
            if (remind) {
                TaskReminder taskReminder = new TaskReminder(description, duration);
                taskReminder.start();
            }
            duplicateCheck = CheckAnomaly.isDuplicate(assignment);
            if (duplicateCheck == -1) {
                return assignment;
            } else {
                throw new DuplicateException(duplicateCheck);
            }
        } else if (type.equals("leave") || type.equals("lv")) {
            String user;
            String[] leaveUserArray = input.split("@");
            if (leaveUserArray.length != 1) {
                user = leaveUserArray[1].trim();
            } else {
                throw new OfficeShareException(ExceptionType.emptyUser);
            }
            Leave leave = new Leave(description, user, from, to);
            leave.setPriority(priority);
            leave.setRecurrenceSchedule(recurrence);
            duplicateCheck = CheckAnomaly.isDuplicate(leave);
            if (duplicateCheck == -1) {
                return leave;
            } else {
                throw new DuplicateException(duplicateCheck);
            }
        } else if (type.equals("meeting") || type.equals("mt")) {
            if (remind) {
                if (unit.equals(TimeUnit.unDefined)) {
                    // duration was not specified or not correctly input
                    Meeting meeting = new Meeting(description, date);
                    meeting.setPriority(priority);
                    meeting.setAssignee(assignee);
                    meeting.setRecurrenceSchedule(recurrence);
                    TaskReminder taskReminder = new TaskReminder(description, duration);
                    taskReminder.start();
                    duplicateCheck = CheckAnomaly.isDuplicate(meeting);
                    if (duplicateCheck == -1) {
                        timeClashCheck = CheckAnomaly.isTimeClash(meeting);
                        if (timeClashCheck == -1) {
                            return meeting;
                        } else {
                            throw new TimeClashException(timeClashCheck);
                        }
                    } else {
                        throw new DuplicateException(duplicateCheck);
                    }

                } else {
                    Meeting meeting = new Meeting(description, date, duration, unit);
                    meeting.setPriority(priority);
                    meeting.setAssignee(assignee);
                    meeting.setRecurrenceSchedule(recurrence);
                    TaskReminder taskReminder = new TaskReminder(description, duration);
                    taskReminder.start();
                    duplicateCheck = CheckAnomaly.isDuplicate(meeting);
                    if (duplicateCheck == -1) {
                        timeClashCheck = CheckAnomaly.isTimeClash(meeting);
                        if (timeClashCheck == -1) {
                            return meeting;
                        } else {
                            throw new TimeClashException(timeClashCheck);
                        }
                    } else {
                        throw new DuplicateException(duplicateCheck);
                    }
                }
            } else {
                if (unit.equals(TimeUnit.unDefined)) {
                    // duration was not specified or not correctly input
                    Meeting meeting = new Meeting(description, date);
                    meeting.setPriority(priority);
                    meeting.setAssignee(assignee);
                    meeting.setRecurrenceSchedule(recurrence);
                    duplicateCheck = CheckAnomaly.isDuplicate(meeting);
                    if (duplicateCheck == -1) {
                        timeClashCheck = CheckAnomaly.isTimeClash(meeting);
                        if (timeClashCheck == -1) {
                            return meeting;
                        } else {
                            throw new TimeClashException(timeClashCheck);
                        }
                    } else {
                        throw new DuplicateException(duplicateCheck);
                    }
                } else {
                    Meeting meeting = new Meeting(description, date, duration, unit);
                    meeting.setPriority(priority);
                    meeting.setAssignee(assignee);
                    meeting.setRecurrenceSchedule(recurrence);
                    duplicateCheck = CheckAnomaly.isDuplicate(meeting);
                    if (duplicateCheck == -1) {
                        timeClashCheck = CheckAnomaly.isTimeClash(meeting);
                        if (timeClashCheck == -1) {
                            return meeting;
                        } else {
                            throw new TimeClashException(timeClashCheck);
                        }
                    } else {
                        throw new DuplicateException(duplicateCheck);
                    }
                }
            }
        } else {
            throw new OfficeShareException(ExceptionType.wrongTaskType);
        }
    }

    /**
     * Update a task from the task list according to the user's input.
     * @param input user's input
     * @param oldTask the task to be updated
     */
    public void updateTask(String input, Task oldTask) throws OfficeShareException {
        boolean isNotUpdated = true;
        boolean isSetToEveryone = false;

        String description = this.extractField(input,"-");
        if (description != null) {
            oldTask.setDescription(description);
            isNotUpdated = false;
        }

        if (input.contains("&")) {
            ArrayList<Date> dates = extractDate(input);
            if (oldTask instanceof Leave && dates.size() == 2) {
                Leave oldLeave = (Leave) oldTask;
                Date start = dates.get(0);
                Date end = dates.get(1);
                oldLeave.setDate(start);
                oldLeave.setStartDate(start);
                oldLeave.setEndDate(end);
                isNotUpdated = false;
            } else {
                Date date = dates.get(0);
                if (oldTask instanceof Leave) {
                    Leave oldLeave = (Leave)oldTask;
                    oldLeave.setEndDate(date);
                    isNotUpdated = false;
                } else {
                    oldTask.setDate(date);
                    isNotUpdated = false;
                }
            }
        }

        if (input.contains("*")) {
            Priority priority = this.extractPriority(input);
            oldTask.setPriority(priority);
            isNotUpdated = false;
        }

        if (input.contains("@")) {
            String assignee = null;
            try {
                assignee = this.extractAssignee(input);
            } catch (OfficeShareException e) {
                assignee = "everyone";
            }
            if (assignee.equals("everyone")) {
                isSetToEveryone = true;
            }
            oldTask.setAssignee(assignee);
            if (oldTask instanceof Leave) {
                Leave oldLeave = (Leave) oldTask;
                oldLeave.setUser(assignee);
            }
            isNotUpdated = false;
        }

        if (input.contains("^") && oldTask instanceof Meeting) {
            Pair<Integer, TimeUnit> durationAndUnit = this.extractDuration(input);
            int duration = durationAndUnit.getKey();
            TimeUnit unit = durationAndUnit.getValue();
            Meeting oldMeeting = (Meeting) oldTask;
            oldMeeting.setDuration(duration,unit);
            isNotUpdated = false;
        }

        if (input.contains("%")) {
            RecurrenceScheduleType recurrence = this.extractRecurrence(input);
            oldTask.setRecurrenceSchedule(recurrence);
            isNotUpdated = false;
        }

        // check if any field was updated at all
        if (isNotUpdated) {
            throw new OfficeShareException(ExceptionType.invalidInputString);
        }

        if (isSetToEveryone) {
            throw new OfficeShareException(ExceptionType.assigneeSetToEveyone);
        }
    }

    /**
     * Updates the date of the overdue task.
     * @param input user's input of the date
     * @param overdueTask the task which date needs to be updated
     */
    public void rescheduleTask(String input, Task overdueTask) throws OfficeShareException {
        ArrayList<Date> dates = this.extractDate(input);
        if (overdueTask instanceof Leave && dates.size() == 2) {
            Leave oldLeave = (Leave) overdueTask;
            Date start = dates.get(0);
            Date end = dates.get(1);
            oldLeave.setDate(start);
            oldLeave.setStartDate(start);
            oldLeave.setEndDate(end);
        } else {
            Date date = dates.get(0);
            overdueTask.setDate(date);
        }
    }
}
