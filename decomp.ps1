param(
    [ValidateSet('generate','build','compare','status','report','test','worklist','profiles')]
    [string]$Action = 'status'
)
$ErrorActionPreference = 'Stop'
Push-Location $PSScriptRoot
try {
    switch ($Action) {
        'generate' { & python tools/generate_game.py }
        'build' { & python tools/verify.py }
        'compare' { & python tools/verify.py --check }
        'status' { & python tools/game_progress.py }
        'report' { & python tools/game_progress.py --save --require-verified }
        'test' { & python -m unittest discover -s tests -v }
        'worklist' { & python tools/worklist.py --save }
        'profiles' { & python tools/profile_audit.py --save --summary }
    }
    if ($LASTEXITCODE -ne 0) { throw "Project command failed: $LASTEXITCODE" }
} finally { Pop-Location }
