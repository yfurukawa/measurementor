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
