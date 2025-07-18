import yaml, sys
try:
    with open("config/dev.yaml") as f:
        yaml.safe_load(f)
    print("YAML OK")
except Exception as e:
    print("YAML error:", e)
    sys.exit(1)
