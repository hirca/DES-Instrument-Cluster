varying highp vec2 qt_TexCoord0;
uniform highp vec2 center;
uniform highp float startAngle;
uniform highp float endAngle;
uniform highp vec4 zoneColors[3];  // Adjust size if needed
uniform highp float zoneEndAngles[3];  // Adjust size if needed
uniform int zoneCount;
uniform highp float arcWidth;

void main() {
    highp vec2 pos = qt_TexCoord0 - center;
    highp float angle = atan(pos.y, pos.x);
    if (angle < 0.0) angle += 2.0 * 3.14159;
    
    highp float dist = length(pos);
    
    if (dist > 0.5 || dist < 0.5 - arcWidth) {
        gl_FragColor = vec4(0, 0, 0, 0);
        return;
    }
    
    if (angle >= startAngle && angle <= endAngle) {
        for (int i = 0; i < zoneCount; i++) {
            if (angle <= zoneEndAngles[i]) {
                highp float t = smoothstep(0.5 - arcWidth, 0.5, dist);
                gl_FragColor = mix(vec4(0, 0, 0, 0), zoneColors[i], t);
                return;
            }
        }
    }
    
    gl_FragColor = vec4(0, 0, 0, 0);
}
