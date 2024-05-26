DROP DATABASE project_metrics;
CREATE DATABASE project_metrics;

\c project_metrics

DROP TABLE task_metrics;

CREATE TABLE task_metrics (
  taskid integer PRIMARY KEY,
  metrics_data jsonb
);

DROP TABLE rework_times;

CREATE TABLE rework_times (
  taskid integer PRIMARY KEY,
  reworkTimes integer
);

CREATE TABLE previous_task (
  taskid        integer PRIMARY KEY,
  taskName      text,
  projectId     integer,
  projectName   text,
  sprintId      integer,
  sprintName    text,  
  author        text,
  itemId        integer,
  estimatedTime real,
  assignee      text,
  satus         char(15),
  statusCode    integer,
  updatedAt     char(25)
);
