import pandas as pd


def SQL_to_pandas(cursor):
    columns = []
    for d in cursor.description:
        columns.append(d[0])
    return pd.DataFrame(cursor.fetchall(), columns=columns)
