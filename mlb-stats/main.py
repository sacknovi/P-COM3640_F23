import json
from fastapi import FastAPI, HTTPException
import pandas as pd
from typing import Optional

from formula_lexer import CalcLexer
from formula_parser import CalcParser

# Open and load the JSON file
formulas = {}
with open("resources/metrics.json", "r") as file:
    data = json.load(file)
    # Extract formulas from the loaded JSON data
    for metric in data.get("metrics", []):
        key = metric.get("key")
        value = metric.get("value")
        if key and value:
            formulas[key] = value

# Create an instance of the lexer
lexer = CalcLexer()

# Load the CSV data into a pandas DataFrame
df = pd.read_csv("resources/mlb_2021_batter_stats.csv")

# Iterate over DataFrame rows
for index, row in df.iterrows():
    # Convert the row to a dictionary
    env = row.to_dict()

    # Iterate over all formulas and tokenize
    for key, formula in formulas.items():
        try:
            env[key] = lexer.tokenize(formula)
            #for token in lexer.tokenize(formula):
                #print(token)
        except Exception as e:
            print(f"Error lexing formula {key} for player {env['PLAYER']}: {str(e)}")
            env[key] = None
        
    # Create new parser for the player with the env as the row data
    # formualas to parse are already part of the env
    parser = CalcParser(env)

    # Iterate over all formula keys
    for key, formula in formulas.items():
        try:
            result = parser.parse(key)
            if type(result) == bool:
                df[key] = df[key].astype('bool')
            df.at[index, key] = result
        except Exception as e:
            print(f"Error parsing formula {key} for player {env['PLAYER']}: {str(e)}")


app = FastAPI()

@app.get("/players/player/{player_id}")
async def get_player(player_id: int):
    # Filter the DataFrame for the specified player_id
    player_data = df[df["ID"] == player_id].to_dict(orient="records")

    # Check if player data is found
    if not player_data:
        raise HTTPException(status_code=404, detail="Player not found")

    # Return the player data
    return player_data[0]


@app.get("/players/")
async def get_data(
    position: Optional[str] = None,
    infielder: Optional[bool] = None,
    veteran: Optional[bool] = None,
):
    df_filtered = df.copy()

    # Filter by position if provided
    if position:
        df_filtered = df_filtered[df_filtered["POSITION"] == position]

    # Filter by infielder flag if infielder is provided
    if infielder is not None:
        df_filtered = df_filtered[df_filtered["infielder"] == infielder]

    # Filter by veteran flag if veteran is provided
    if veteran is not None:
        df_filtered = df_filtered[df_filtered["veteran"] == veteran]

    # Convert the filtered DataFrame to a JSON-like dictionary and return
    return df_filtered.to_dict(orient="records")
